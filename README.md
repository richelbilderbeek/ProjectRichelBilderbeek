#ProjectRichelBilderbeek

Richel Bilderbeek's work

## What ProjectRichelBilderbeek is

ProjectRichelBilderbeek consists of:
* A collection of console, desktop (Qt and VCL) and web (Wt) applications
* A desktop application called ProjectRichelBilderbeekDesktop (in Projects) containing the bundled (Qt) desktop applications
* A web application called ProjectRichelBilderbeekWebsite (in Projects) containing the bundled (Wt) web applications
* A console application called ProjectRichelBilderbeekConsole (in Projects) containing the bundled console applications
* C++ Builder Windows-only code, to be ported to cross-platform Qt Creator code
* The core of Richel Bilderbeek's HTML website

## Where to start

End-users can choose to checkout the stable 'master' branch or the bleeding edge 'develop' branch.
Developers should fork from the 'develop' branch (see also 'Git policy').

### Build prerequisites

In the folder 'Libraries', there are multiple scripts for unzipping or downloading and building libraries:
* mxe.sh: downloads and builds the MXE cross compiler
* fparser.sh: unzips Warp's function parser
* bigint.sh: unzips Matt McCutchen's BigInteger library
* qwt-6.0.1.sh: unzips the 6.0.1 version of the Qwt library
* qwt-6.1.0.sh: downloads the 6.1.0 version of the Qwt library (as long as it is present)
* tesseract-3.00.sh: unzips my modified version of the Tesseract OCR library
* libcvautomation: downloads and build the libcvautomation GUI testing library

### Build all

* Create a folder ~/bin . For me this is '/home/richel/bin'
* Run the script 'Status.sh'

Status.sh will try to compile and crosscompile all programs and copy the executables to ~/bin. This will take multiple hours (on my computer).

### Build ProjectRichelBilderbeek only

The main .pro files are
* /Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pro: contains the bundled (Qt) desktop applications
* /Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekWebsite.pro: contains the bundled (Wt) web applications
* /Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekConsole.pro: contains the bundled console applications

Building one of these projects will take about half an hour (on my computer).

### Build individual projects

Find a .pro file, open it in Qt Creator and compile and run it. Some projects take seconds, other half an hour (on my computer).

## What it is not

ProjectRichelBilderbeek does not include (except by accident):
* Binaries (zipped nor unzipped)
* Zipped source
* HTML pages for viewing the source

This to not be too big of a burden for github.

## Dependencies

Libraries used that are also in this repository are:
* [Boost (version 1.53.0)](http://www.boost.org)
* [Qwt (version 6.0.01)](http://qwt.sourceforge.net)
* [Warp's function parser (versions 4.4.3 and 4.5.1)](http://warp.povusers.org/FunctionParser)
* [Matt McCutchen's BigInteger (version 2010.04.30)](https://mattmccutchen.net/bigint)

These libraries are added to allow easy crosscompilation to Windows using the often-supplied 'crosscompile.sh' or '[...]ToWindows.sh' scripts. 
For crosscompiling from Lubuntu to Windows I use [MXE](https://github.com/mxe/mxe).

## Questions and feature requests

Questions and feature requests can be done by creating a new issue or sending an email to the address at [Richel Bilderbeek's HTML webpage](http://www.richelbilderbeek.nl).

## Git policy

I follow the branching policy from [this article](http://nvie.com/posts/a-successful-git-branching-model), using only
three types: master, develop and feature branches.
* After every push to the master branch, ProjectRichelBilderbeek* must all compile
* Only the develop branch pushes to master
* The feature branch branches and merges with the develop branch

## External links

* [Richel Bilderbeek's HTML webpage](http://www.richelbilderbeek.nl)
