import argparse, re, sys, os

from cncocr import graph, parser

from jinja2 import Environment, PackageLoader
templateEnv = Environment(loader=PackageLoader('cncocr'), extensions=['jinja2.ext.with_','jinja2.ext.do'])

# Arguments
argParser = argparse.ArgumentParser(prog="cncocr_t", description="Process CnC-OCR graph spec.")
argParser.add_argument('--log', action='store_true', help="turn on debug logging for CnC steps")
argParser.add_argument('--platform', choices=['x86', 'ocr'], default='x86', help="target platform for the CnC-OCR runtime")
argParser.add_argument('specfile', help="CnC-OCR graph spec file")
args = argParser.parse_args()

# Check spec file name
nameMatch = re.match(r'^(.*/)?(?P<name>[a-zA-Z]\w*)(?P<cnc>\.cnc)?$', args.specfile)
if not nameMatch:
    sys.exit("ERROR! Bad spec file name: {}".format(args.specfile))
elif not nameMatch.group('cnc'):
    print "WARNING! Spec file name does not end with '.cnc' extension: {}".format(args.specfile)

# Parse graph spec
graphAst = parser.cncGraphSpec.parseFile(args.specfile, parseAll=True)
graphData = graph.CnCGraph(nameMatch.group('name'), graphAst)

supportSrcDir = "./cncocr_support"
if not os.path.exists(supportSrcDir):
    os.makedirs(supportSrcDir)

def writeTemplate(templatepath, namepattern=None, overwrite=True, destdir=supportSrcDir, step=None, refpath=None):
    templatename = os.path.basename(refpath if refpath else templatepath)
    filename = namepattern.format(gname=graphData.name, fname=templatename, sname=step) if namepattern else templatename
    outpath = "{}/{}".format(destdir, filename)
    if overwrite or not os.path.isfile(outpath):
        template = templateEnv.get_template(templatepath)
        contents = template.render(g=graphData, targetStep=step, logEnabled=args.log)
        with open(outpath, 'w') as outfile:
            outfile.write(contents)
            outfile.close()
        print "Writing file: {}".format(outpath)
    elif not overwrite:
        print "Skipping file (already exists): {}".format(outpath)

def writeArchTemplate(path, **kwargs):
    templatepath = path.format("."+args.platform)
    refpath = path.format("")
    writeTemplate(templatepath, refpath=refpath, **kwargs)

# Generate graph scaffolding files
prependedPattern = "{gname}{fname}"
writeTemplate("Graph.h", namepattern="{gname}.h")
writeTemplate("_internal.h", namepattern=prependedPattern)
writeTemplate("_step_ops.c", namepattern=prependedPattern)
writeTemplate("_item_ops.c", namepattern=prependedPattern)
writeArchTemplate("_graph_ops{}.c", namepattern=prependedPattern)
writeTemplate("_steplist.mk", namepattern=prependedPattern)

# Generate runtime files
writeTemplate("runtime/cncocr_internal.h")
writeArchTemplate("runtime/cncocr{}.h")
writeArchTemplate("runtime/cncocr{}.c")

# Write files for user to edit
userTemplateArgs=dict(overwrite=False, destdir=".")
writeTemplate("Makefile", **userTemplateArgs)
writeTemplate("_defs.h", namepattern=prependedPattern, **userTemplateArgs)
writeTemplate("Graph.c", namepattern="{gname}.c", **userTemplateArgs)
writeTemplate("Main.c", **userTemplateArgs)
stepArgs=dict(userTemplateArgs, namepattern="{gname}_{sname}.c")
for stepName in graphData.stepFunctions.keys():
    writeTemplate("StepFunc.c", step=stepName, **stepArgs)

