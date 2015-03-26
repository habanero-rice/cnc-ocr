from itertools import count, ifilter, imap, chain
from sys import exit
from string import strip
# Compatibility for Python 2.6
from counter import Counter
from ordereddict import OrderedDict


def expandExpr(x):
    return x and x.replace("@", "args->").replace("#", "ctx->")


class CType(object):
    """C-style data type"""
    def __init__(self, typ, arrayTyp):
        self.baseType = typ.baseType
        self.stars = typ.get('stars', "")
        self.isVecType = bool(arrayTyp)
        if self.isVecType: self.stars += "*"
        self.isPtrType = bool(self.stars)
        self.ptrType = str(self) + ("" if self.isPtrType else "*")
        self.vecSizeRaw = arrayTyp and arrayTyp.arraySize
        self.vecSize = expandExpr(self.vecSizeRaw)
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
        self.start = CExpr(rtc.start or "0")
        self.end = CExpr(rtc.end)
        self.inclusive = bool(rtc.inclusive)
        if str(self.start) == "0":
            self.sizeExpr = str(self.end)
        elif str(self.start).isalnum() and str(self.end).isalnum():
            self.sizeExpr = "({0}-{1})".format(self.end, self.start)
        else:
            self.sizeExpr = "({0})-({1})".format(self.end, self.start)
        self.upperLoopBound = self.sizeExpr
        if self.inclusive:
            self.sizeExpr = "({0}+1)".format(self.sizeExpr)
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
    def __init__(self, itemRef):
        self.kind = 'ITEM'
        self.collName = itemRef.collName
        self.key = map(makeTagComponent, tuple(itemRef.key))
        self.binding = itemRef.binding
        self.keyRanges = tuple(x for x in self.key if x.isRanged)
    def setBinding(self, b):
        self.binding = b


class RefBlock(object):
    def __init__(self, block, makeRefs):
        self.kind = block.kind
        self.rawCond = block.cond.strip()
        self.cond = expandExpr(self.rawCond)
        self.refs = makeRefs(block.refs)


class ItemDecl(object):
    def __init__(self, itemDecl):
        self.collName = itemDecl.collName
        self.type = CType(itemDecl.type, itemDecl.vecSuffix)
        self.key = tuple(itemDecl.key)
        self.isSingleton = len(self.key) == 0
        self.isVirtual = False


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
        stepTag = list(stepIO.step.tag)
        self.collName = stepIO.step.collName
        self.tag = stepTag
        self.inputItems = []
        self.outputItems = []
        # Verify that tag bindings are unique
        if len(set(stepTag)) != len(stepTag):
            exit("Repeated ID in tag for declaration of step `{0}`: {1}".format(\
                    stepIO.step.collName, stepTag))
        # Helper
        def makeRefs(xs, itemsOutList):
            def makeRefsHelp(xs):
                prevCond = None
                def makeRef(x):
                    if (x.kind == 'ALWAYS'):
                        return makeRefsHelp(x.refs)
                    elif (x.kind in ['IF', 'ELSE', 'ALWAYS']):
                        block = RefBlock(x, makeRefsHelp)
                        if x.kind == 'ELSE':
                            # XXX - I'd rather not use the C-specific '!' operator here
                            block.cond = "!({0})".format(prevCond)
                        prevCond = block.cond
                        return [ block ]
                    elif (x.kind == 'ITEM'):
                        i = ItemRef(x)
                        itemsOutList.append(i)
                        return [ i ]
                    elif (x.kind == 'STEP'):
                        return [ StepRef(x) ]
                    else:
                        exit("Unknown component type: " + x.kind)
                return list(chain(*map(makeRef, xs)))
            return makeRefsHelp(xs)
        # Process inputs and outputs
        self.inputs = makeRefs(stepIO.inputs, self.inputItems)
        self.outputs = makeRefs(stepIO.outputs, self.outputItems)
        # Check all requrested bindings for repeats
        allItems = list(chain(self.inputItems, self.outputItems))
        def getItemName(i): return i.binding or i.collName
        bindingsCounts = Counter(chain(stepTag, map(getItemName, allItems)))
        # Compute binding names (avoiding duplicates)
        bindings = set(bindingsCounts.keys())
        for i in allItems:
            binding = getItemName(i)
            # handle collisions
            if bindingsCounts[binding] > 1:
                f = lambda b: not b in bindings
                g = lambda x: binding+str(x)
                # try appending integers and pick the first one that works
                binding = ifilter(f, imap(g, count())).next()
                bindings.add(binding)
            # record the chosen (unique) binding
            i.setBinding(binding)
        # build the step input count expression
        self.inputCountExpr = " + ".join(["*".join([x.sizeExpr for x in i.keyRanges]) or "1" for i in self.inputItems]) or "0"
        # ranged inputs
        self.rangedInputItems = [ x for x in self.inputItems if x.keyRanges ]

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
        self.ctxParams = filter(bool, map(strip, g.ctx.splitlines())) if g.ctx else []

    def lookupType(self, item):
        return self.itemDeclarations[item.collName].type

