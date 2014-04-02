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

## The ProjectRichelBilderbeek galleries

For an overview of all games, projects and tools in ProjectRichelBilderbeek, visit the gallery pages:
* [Classes gallery](http://www.richelbilderbeek.nl/CppClassGallery.htm)
* [Games gallery](http://www.richelbilderbeek.nl/GameGallery.htm)
* [Projects gallery](http://www.richelbilderbeek.nl/ProjectGallery.htm)
* [Tools gallery](http://www.richelbilderbeek.nl/ToolGallery.htm)

## I want to collaborate!

ProjectRichelBilderbeek encourages collaboration, and already has had contributions from many people, 
and their names are mentioned in the appropriate places for eternal glory.

You can collaborate by
* email richelbilderbeek (at [Richel Bilderbeek's webpage its 'Contact Me' section](http://www.richelbilderbeek.nl/Contact.htm))
* add a GitHub issue: this can be a question, suggestion, or whatever
* fork this repository, make the changes, and submit a pull request. 

richelbilderbeek has promised never to bite :)

### Forking and pull requests

End-users can choose to checkout the stable 'master' branch or the bleeding edge 'develop' branch.
Developers should fork from the 'develop' branch (see also 'Git policy').

For HTML code, richelbilderbeek will accept the pull request when:
* it improves the content in an undiable aspect (e.g. correcting a spelling error)
* it improves the content with a reference to the literature (as stated in [Richel Bilderbeek's its goals](http://www.richelbilderbeek.nl/CppGoal.htm))

For C++ code, richelbilderbeek will accept the pull request when:
* it shows the current code to fail, either with a certain input, or with an added test
* the new suggested still passes all current tests, and additionally the test the normal code fails
* the coding standard is maintained: GNU brackets, two spaces instead of tabs, const-correct, asserts, sufficient documentation (as stated in [Richel Bilderbeek's its goals](http://www.richelbilderbeek.nl/CppGoal.htm))

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

See [the Git workflow ](git_workflow.md).

## External links

* [Richel Bilderbeek's HTML webpage](http://www.richelbilderbeek.nl)
