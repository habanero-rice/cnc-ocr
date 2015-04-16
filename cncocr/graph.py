from itertools import count, ifilter, imap
from collections_27 import Counter, OrderedDict
from sys import exit
from string import strip

def expandExpr(x, collID="0", numRanks="CNC_NUM_RANKS"):
    return (x.strip()
            .replace("@", "args->").replace("#", "ctx->")
            .replace("$ID", collID).replace("$RANKS", numRanks))

class CType(object):
    """C-style data type"""
    def __init__(self, typ):
        self.baseType = typ.baseType
        self.stars = typ.get('stars', "")
        self.isPtrType = bool(self.stars)
        self.ptrType = str(self) + ("" if self.isPtrType else "*")
    def __str__(self):
        return "{0} {1}".format(self.baseType, self.stars)


class CExpr(object):
    """C-style expression"""
    def __init__(self, expr):
        self.raw = expr.strip()
        self.expanded = expandExpr(self.raw)
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
        self.sizeExpr = "(({0})-({1}))".format(self.end, self.start)
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
        self.raw_condition = itemRef.condition
        if self.raw_condition:
            assert not self.keyRanges, "Conditions on scalar inputs only"
            self.raw_condition = self.raw_condition.strip()
            self.condition = expandExpr(self.raw_condition)


class ItemDecl(object):
    def __init__(self, itemDecl):
        self.collName = itemDecl.collName
        self.type = CType(itemDecl.type)
        self.key = tuple(itemDecl.key)
        self.isSingleton = len(self.key) == 0
        self.isVirtual = False


class StepMapping(object):
    def __init__(self, vstep):
        self.collName = vstep.collName
        self.tag = tuple(x.strip() for x in vstep.tag)
        self.mapTarget = vstep.targetCollName
        self.mappedTag = tuple(x.strip() for x in vstep.tagFunc)


class ItemMapping(ItemDecl):
    def __init__(self, itemDecl):
        super(ItemMapping, self).__init__(itemDecl)
        self.mapTarget = itemDecl.targetCollName
        self.isVirtual = True


class ItemInlineMapping(ItemMapping):
    def __init__(self, itemDecl):
        super(ItemInlineMapping, self).__init__(itemDecl)
        self.keyFunction = tuple(x.strip() for x in itemDecl.keyFunc)
        self.isInline = True


class ItemExternMapping(ItemMapping):
    def __init__(self, itemDecl):
        super(ItemExternMapping, self).__init__(itemDecl)
        self.functionName = itemDecl.funcName
        self.isInline = False


def makeItemDecl(itemDecl):
    vm = itemDecl.virtualMapping
    if not vm:
        return ItemDecl(itemDecl)
    elif vm.keyFunc:
        return ItemInlineMapping(itemDecl)
    else:
        return ItemExternMapping(itemDecl)


class StepFunction(object):
    def __init__(self, stepIO):
        # Helper functions for dealing with item/step references
        def getBinding(i): return i.binding or i.collName
        def isItem(x): return x.kind == 'ITEM'
        # Check all requrested bindings for repeats
        inputs = list(stepIO.inputs)
        assert all(len(i.tagRanges) <= 1 for i in inputs), "Only allow 1 ranged component allowed in inputs"
        outputs = list(stepIO.outputs)
        allItems = inputs + filter(isItem, outputs)
        stepTag = list(stepIO.step.tag)
        bindingsCounts = Counter(map(getBinding, allItems) + stepTag)
        # Verify that tag bindings are unique
        if len(set(stepTag)) != len(stepTag):
            exit("Repeated ID in tag for declaration of step `{0}`: {1}".format(\
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
        exit("Repeated {0} collection names: {1}".format(typ, ", ".join(repeated)))


def verifyEnv(stepFuns):
    for name in [initNameRaw, finalizeNameRaw]:
        if not name in stepFuns:
            exit("Missing I/O declaration for environment ({0}).".format(name))


# TODO - verify item/step instances match with their declarations

class CnCGraph(object):
    def __init__(self, name, g):
        verifyCollectionDecls("item", g.itemColls)
        steps = [ x.step for x in g.stepRels ]
        verifyCollectionDecls("step", steps)
        self.name = name
        # items
        self.itemDeclarations = OrderedDict((i.collName, makeItemDecl(i)) for i in g.itemColls)
        self.concreteItems = [ i for i in self.itemDeclarations.values() if not i.isVirtual ]
        # item virtual mappings
        self.vms = [ i for i in self.itemDeclarations.values() if i.isVirtual ]
        self.inlineVms = [ i for i in self.vms if i.isInline ]
        self.externVms = [ i for i in self.vms if not i.isInline ]
        # steps / pseudo-steps
        self.stepFunctions = OrderedDict((x.step.collName, StepFunction(x)) for x in g.stepRels)
        verifyEnv(self.stepFunctions)
        self.initFunction = self.stepFunctions.pop(initNameRaw)
        self.initFunction.collName = str(name)+"_init"
        self.finalizeFunction = self.stepFunctions.pop(finalizeNameRaw)
        self.finalizeFunction.collName = str(name)+"_finalize"
        self.finalAndSteps = [self.finalizeFunction] + self.stepFunctions.values()
        # context
        self.ctxParams = filter(bool, map(strip, g.ctx.fields.splitlines())) if g.ctx else []

    def lookupType(self, item):
        return self.itemDeclarations[item.collName].type

class DistFn(object):
    def __init__(self, expr, collID, numRanks):
        self.raw = expr.strip()
        self.expanded = expandExpr(self.raw, collID, numRanks)
    def __str__(self):
        return self.expanded

class CnCTuningInfo(object):
    def __init__(self, g, ast):
        self.g = g
        if ast:
            self.itemColls = dict([ (x.collName, x) for x in ast.itemColls ])
            self.stepColls = dict([ (x.collName, x) for x in ast.stepColls ])
            self.tuningGroups = OrderedDict(
                    (x.step.collName, StepFunction(x)) for x in ast.groups)
            self.initTuning = self.tuningGroups.pop(initNameRaw)
            self.vSteps = dict([ (x.collName, StepMapping(x)) for x in ast.vSteps ])
        else:
            self.itemColls = {}
            self.stepColls = {}
            self.tuningGroups = {}
            self.vSteps = {}
        self.steplikes = g.finalAndSteps + self.tuningGroups.values()
        # virtual steps
        # verify
        for g in self.tuningGroups.values():
            for x in g.inputs:
                if isTuningGroup(x) and not len(x.tagRanges) <= 1:
                    exit("Only allow 1 ranged component allowed for tuning group references")
            for x in g.outputs:
                if x.kind == 'ITEM':
                    exit("Tuning groups can't put items")

    def isTuningGroup(self, x):
        return x.collName in self.tuningGroups.keys()

    def itemHasDistFn(self, collName):
        return bool(self.itemColls.get(collName))

    def itemDistFn(self, collName, collID, numRanks):
        entry = self.itemColls.get(collName)
        if entry:
            return DistFn(entry.distFn, collID, numRanks)
        else:
            coll = self.g.itemDeclarations[collName]
            distVar = coll.key[0] if coll.key else collID
            return  "{0} % {1}".format(distVar, numRanks)

    def getFnDecl(self, collName):
        return (self.g.stepFunctions.get(collName, self.tuningGroups.get(collName))
                or self.vSteps.get(collName))

    def stepHasDistFn(self, collName):
        return bool(self.stepColls.get(collName))

    def stepDistFn(self, collName, collID, numRanks):
        entry = self.stepColls.get(collName)
        if entry:
            return DistFn(entry.distFn, collID, numRanks)
        else:
            coll = self.getFnDecl(collName)
            distVar = coll.tag[0] if coll.tag else collID
            return  "{0} % {1}".format(distVar, numRanks)
