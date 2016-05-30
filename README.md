CnC on HCMPI with Tuning
========================

This codebase is a branch of the CnC-OCR repository,
swapping the underlying runtime from OCR to HCMPI.
We used revision 47427 of the HCMPI code located at
<https://svn.rice.edu/r/parsoft/src/Habanero-C/branches/hpt-comm>.
For more information on HCMPI, see [1].

This branch also adds support for specifying hierarchical
groupings of computation steps into affinity groups,
and declaring distribution functions for placement
of both computation steps and data items.

Tuning specifications are declared in a `*.cnct` file,
while the domain specification given in a `*.cnc` file.
See the `examples` directory for some sample programs.
For a more detailed discussion of tuning in CnC, see [2].

See `cnc-ocr-readme.txt` for general instructions on using this framework.
The translator tool has a new `-t` option for providing a tuning file.

------

[1] <i>Integrating Asynchronous Task Parallelism with MPI.</i>
Sanjay Chatterjee, Sagnak Tasirlar, Zoran Budimlic, Vincent Cave, Milind Chabbi, Max Grossman, Yonghong Yan, Vivek Sarkar.
IEEE International Parallel & Distributed Processing Symposium (IPDPS), May 2013.

[2] <i>Declarative Tuning for Locality in Parallel Programs.</i>
Sanjay Chatterjee, Nick Vrvilo, Zoran Budimlic, Kathleen Knobe, Vivek Sarkar.
Proceedings of the International Conference on Parallel Processing (ICPP) 2016, August 2016.

Both papers are available on the Habanero group's publications page:
<https://habanero.rice.edu/publications/>
