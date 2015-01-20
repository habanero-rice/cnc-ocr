*
* Installation Prerequisites
*
	- make
	- Python (2.7)
	- gcc
	- OCR (0.9)

*
* Setting up the environment
*

If you have a copy of the xstack repository, the CnC-OCR root directory (which
contains this README) should be in the xstack/hll directory. The expected
directory structure is as follows:

   - xstack/ : the root xstack source directory
   - xstack/ocr/ : the source root for OCR
   - xstack/hll/ : high-level-libraries for OCR
   - xstack/hll/cncocr/ : CnC-OCR root directory (name doesn't matter)

If you don't have a copy of the xstack repository, you can still mimic this
directory structure to get the expected behavior. To set the needed environment
variables, navigate to the CnC-OCR root directory and source setup_env.sh:

	source setup_env.sh

This script sets the XSTACK_SRC variable to point to the xstack repository root,
CNCOCR_INSTALL to point to the CnC-OCR root, and updates the PATH to include
the CnC-OCR bin directory (which contains the graph translator tool).

*
* Running the translator
*
	cncocr_t [options] FileName.cnc

The first time you run the graph translator, it will download its dependencies (Jinja2 and Pyparsing), which will be saved in ${CNCOCR_INSTALL}/lib for future use.

*
* Docs
*

Please visit the CnC-OCR wiki on Github for current documentation.
   https://github.com/habanero-rice/cnc-ocr/wiki

Some additional documentation on the CnC model can be found in docCnCHC.pdf, a document created part of the CDSC project. 
Despite the fact that the document was designed for CnC-HC rather than CnC-OCR, it is never the less informative about creating a .cnc file and changing it, concepts that still apply for CnC-OCR. The document can be found on our github page:
	https://github.com/habanero-rice/cnc-ocr/blob/master/docCnCHC.pdf

============================================================================
*
* Creating CnC-OCR applications
*

1) For any CnC-OCR application, the first step is to create the CnC graph file (name.cnc) which will define the steps, item collections and tag collections and the relations between them.
2) The second step is invoking the translator:
cncc_t graph_name.cnc
   This will generate a bunch of files. The files generated in the current directory should be edited by the application author. The files in the cncocr_support directory interfaces the user code with the underlying OCR runtime and should rarely need any editing.
3) The third step is editing the code in the current directory to implement the graph's init, finalize, and step functions. Additionally, you may need to edit the mainEdt (in Main.c) to parse command-line arguments and pass them to the CnC graph when launched.
4) make run ARGS="arg1 arg2 arg3 ..."

See the examples (in the examples directory) for further details.


*
* Help
*
You can submit bug reports and other issues on our github page:
https://github.com/habanero-rice/cnc-ocr

Please also check the github page for current contact information.


*
* Acknowledgements
*
Partial support for CnC-OCR was provided through the CDSC program of 
the National Science Foundation with an award in the 2009 Expedition 
in Computing Program.
This work is actively supported as part ofthe DOE-funded Traleika Glacier
X-Stack project (Intel CS1924113).
