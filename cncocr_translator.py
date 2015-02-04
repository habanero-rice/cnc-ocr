import argparse, re, sys, os

from cncocr import graph, parser

from jinja2 import Environment, PackageLoader
templateEnv = Environment(loader=PackageLoader('cncocr'), extensions=['jinja2.ext.with_','jinja2.ext.do'], keep_trailing_newline=True)

# Arguments
argParser = argparse.ArgumentParser(prog="cncocr_t", description="Process CnC-OCR graph spec.")
argParser.add_argument('--log', action='store_true', help="turn on debug logging for CnC steps")
argParser.add_argument('--platform', choices=['x86', 'ocr'], default='x86', help="target platform for the CnC-OCR runtime")
argParser.add_argument('--full-make', action='store_true', help="Use the full OCR build system by default (changes the Makefile symlink)")
argParser.add_argument('--hpt', action='store_true', help="use HPTs for tuning")
argParser.add_argument('-t', help="optional tuning spec file")
argParser.add_argument('specfile', help="CnC-OCR graph spec file")
args = argParser.parse_args()

# Handle aliases

# Check spec file name
nameMatch = re.match(r'^(.*/)?(?P<name>[a-zA-Z]\w*)(?P<cnc>\.cnc)?$', args.specfile)
if not nameMatch:
    sys.exit("ERROR! Bad spec file name: {0}".format(args.specfile))
elif not nameMatch.group('cnc'):
    print "WARNING! Spec file name does not end with '.cnc' extension: {0}".format(args.specfile)

# Parse graph spec
graphAst = parser.cncGraphSpec.parseFile(args.specfile, parseAll=True)
graphData = graph.CnCGraph(nameMatch.group('name'), graphAst)

# Parse tuning data
tuningAst = parser.cncTuningSpec.parseFile(args.t, parseAll=True) if args.t else None
tuningData = graph.CnCTuningInfo(graphData, tuningAst)

def makeDirP(path):
    if not os.path.exists(path):
        os.makedirs(path)

supportSrcDir = "./cncocr_support"
makeDirP(supportSrcDir)

makefilesDir = "./makefiles"
makeDirP(makefilesDir)

tgSrcDir = "./cncocr_support/tg_src"
makeDirP(tgSrcDir)

def makeLink(target, name):
    if os.path.islink(name):
        os.remove(name)
    if os.path.isfile(name):
        print "Skipping link (already exists): {0}".format(name)
    else:
        print "Creating link: {0} -> {1}".format(name, target)
        os.symlink(target, name)

def writeTemplate(templatepath, namepattern=None, overwrite=True, destdir=supportSrcDir, step=None, refpath=None):
    templatename = os.path.basename(refpath if refpath else templatepath)
    filename = namepattern.format(gname=graphData.name, fname=templatename, sname=step) if namepattern else templatename
    outpath = "{0}/{1}".format(destdir, filename)
    if overwrite or not os.path.isfile(outpath):
        template = templateEnv.get_template(templatepath)
        contents = template.render(g=graphData, targetStep=step, logEnabled=args.log, tuningInfo=tuningData, useHPT=args.hpt)
        with open(outpath, 'w') as outfile:
            outfile.write(contents)
            outfile.close()
        print "Writing file: {0}".format(outpath)
    elif not overwrite:
        print "Skipping file (already exists): {0}".format(outpath)

def writeArchTemplate(path, **kwargs):
    templatepath = path.format("."+args.platform)
    refpath = path.format("")
    writeTemplate(templatepath, refpath=refpath, **kwargs)

# Generate graph scaffolding files
prependedPattern = "{gname}{fname}"
writeTemplate("Graph.h", namepattern="{gname}.h")
writeTemplate("_internal.h", namepattern=prependedPattern)
writeTemplate("_step_ops.hc", namepattern=prependedPattern)
writeTemplate("_item_ops.c", namepattern=prependedPattern)
writeArchTemplate("_graph_ops{0}.c", namepattern=prependedPattern)
writeArchTemplate("_defs{0}.mk", namepattern=prependedPattern)

# Generate runtime files
writeTemplate("runtime/cncocr_internal.h")
writeArchTemplate("runtime/cncocr{0}.h")
writeArchTemplate("runtime/cncocr{0}.c")

# Makefiles
makefileArgs = dict(destdir=makefilesDir, overwrite=False)
writeTemplate("Makefile", namepattern="simple.mk", **makefileArgs)
writeTemplate("makefiles/Makefile", namepattern="full.mk", **makefileArgs)
for suffix in ["tg", "x86-pthread-x86", "x86-pthread-tg", "x86-pthread-mpi"]:
    writeTemplate("makefiles/Makefile."+suffix, **makefileArgs)
defaultMakefile = "full.mk" if args.full_make else "simple.mk"
makeLink("{0}/{1}".format(makefilesDir, defaultMakefile), "Makefile") 

# Support scripts
writeTemplate("makeSourceLinks.sh")
writeTemplate("makefiles/config.cfg", destdir=tgSrcDir)

# Write files for user to edit
userTemplateArgs=dict(overwrite=False, destdir=".")
writeTemplate("_defs.h", namepattern=prependedPattern, **userTemplateArgs)
writeTemplate("_itemInfo.h", namepattern=prependedPattern, **userTemplateArgs)
writeTemplate("Graph.hc", namepattern="{gname}.hc", **userTemplateArgs)
writeTemplate("Main.hc", **userTemplateArgs)
stepArgs=dict(userTemplateArgs, namepattern="{gname}_{sname}.hc")
for stepName in graphData.stepFunctions.keys():
    writeTemplate("StepFunc.hc", step=stepName, **stepArgs)

