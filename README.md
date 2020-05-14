omegaThesis
===========

First of all, an installation of ROOT (with RooFit) is required.

Then, define the environment variable in your local `.bashrc`, located in your home directory

To do so, add this line at the end (PRODIR stands for Project Directory)

PLEASE, note that it says installation directory!! You MUST change it for this location!

> export PRODIR=/installation/directory

Save file and then, in the command line, execute:

> $ source .bashrc

After this, setup `ext/Analyser` and `ext/ClasTool`

Then,

> $ cd ${PRODIR}
> $ make

Everything should work just fine by now!

Just in case, you can set the directory structure by running

$ ./sh/create_dir_structure.sh