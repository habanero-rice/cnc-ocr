from itertools import count, ifilter, imap
from collections import Counter, OrderedDict
from sys import exit


class CType(object):
    """C-style data type"""
    def __init__(self, typ):
        self.baseType = typ.baseType
        self.stars = typ.get('stars', "")
        self.isPtrType = bool(self.stars)
        self.ptrType = str(self) + ("" if self.isPtrType else "*")
    def __str__(self):
        return "{} {}".format(self.baseType, self.stars)


class CExpr(object):
    """C-style expression"""
    def __init__(self, expr):
        self.raw = expr.strip()
        self.expanded = self.raw.replace("@", "args->").replace("#", "ctx->")
    def __str__(self):
        return self.expanded


class ScalarTC(object):
    def __init__(self, stc):
        self.expr = CExpr(stc.expr)
        self.isRanged = False


class RangedTC(object):
    def __init__(self, rtc):
        self.start = CExpr(rtc.start)
        self.end = CExpr(rtc.end)
        self.sizeExpr = "(({})-({}))".format(self.end, self.start)
        self.isRanged = True


def makeTagComponent(tc):
    return RangedTC(tc) if tc.kind == 'RANGED' else ScalarTC(tc)


class StepRef(object):
    def __init__(self, stepRef):
        self.kind = 'STEP'
        self.collName = stepRef.collName
        self.tag = map(makeTagComponent, tuple(stepRef.tag))
        self.tagRanges = tuple(x for x in self.tag if x.isRanged)


class ItemRef(object):
    def __init__(self, itemRef, binding):
        self.kind = 'ITEM'
        self.collName = itemRef.collName
        self.key = map(makeTagComponent, tuple(itemRef.key))
        self.binding = binding
        self.keyRanges = tuple(x for x in self.key if x.isRanged)


class ItemDecl(object):
    def __init__(self, itemDecl):
        self.collName = itemDecl.collName
        self.type = CType(itemDecl.type)
        self.key = tuple(itemDecl.key)
        self.isSingleton = len(self.key) == 0


class StepFunction(object):
    def __init__(self, stepIO):
        # Helper functions for dealing with item/step references
        def getBinding(i): return i.binding or i.collName
        def isItem(x): return x.kind == 'ITEM'
        # Check all requrested bindings for repeats
        inputs = list(stepIO.inputs)
        outputs = list(stepIO.outputs)
        allItems = inputs + filter(isItem, outputs)
        stepTag = list(stepIO.step.tag)
        bindingsCounts = Counter(map(getBinding, allItems) + stepTag)
        # Verify that tag bindings are unique
        if len(set(stepTag)) != len(stepTag):
            exit("Repeated ID in tag for declaration of step `{}`: {}".format(\
                    stepIO.step.collName, stepTag))
        # Compute binding names (avoiding duplicates)
        bindings = set(bindingsCounts.keys())
        itemBindings = {}
        for i in allItems:
            binding = i.binding or i.collName
            # handle collisions
            if bindingsCounts[binding] > 1:
                f = lambda b: not b in bindings
                g = lambda x: binding+str(x)
                # try appending integers and pick the first one that works
                binding = ifilter(f, imap(g, count())).next()
                bindings.add(binding)
            # record the chosen (unique) binding
            itemBindings[i] = binding
        # Helper
        def makeRef(x):
            return ItemRef(x, itemBindings[x]) if isItem(x) else StepRef(x)
        # Init fields
        self.collName = stepIO.step.collName
        self.tag = stepTag
        self.inputs = map(makeRef, inputs)
        self.outputs = map(makeRef, outputs)
        self.inputCountExpr = " + ".join(["*".join([x.sizeExpr for x in i.keyRanges]) or "1" for i in self.inputs]) or "0"
        inputColls = [i.collName for i in self.inputs]
        self.inputColls = list(OrderedDict.fromkeys(inputColls))

initNameRaw = '$init'
finalizeNameRaw = '$finalize'

def verifyCollectionDecls(typ, decls):
    nameCounts = Counter([ x.collName for x in decls ])
    repeated = [ name for name, n in nameCounts.iteritems() if n > 1 ]
    if repeated:
        exit("Repeated {} collection names: {}".format(typ, ", ".join(repeated)))


def verifyEnv(stepFuns):
    for name in [initNameRaw, finalizeNameRaw]:
        if not name in stepFuns:
            exit("Missing I/O declaration for environment ({}).".format(name))


# TODO - verify item/step instances match with their declarations

class CnCGraph(object):
    def __init__(self, name, g):
        verifyCollectionDecls("item", g.itemColls)
        steps = [ x.step for x in g.stepRels ]
        verifyCollectionDecls("step", steps)
        self.name = name
        self.itemDeclarations = OrderedDict((i.collName, ItemDecl(i)) for i in g.itemColls)
        self.stepFunctions = OrderedDict((x.step.collName, StepFunction(x)) for x in g.stepRels)
        verifyEnv(self.stepFunctions)
        self.initFunction = self.stepFunctions.pop(initNameRaw)
        self.initFunction.collName = str(name)+"_init"
        self.finalizeFunction = self.stepFunctions.pop(finalizeNameRaw)
        self.finalizeFunction.collName = str(name)+"_finalize"
        self.finalAndSteps = [self.finalizeFunction] + self.stepFunctions.values()

