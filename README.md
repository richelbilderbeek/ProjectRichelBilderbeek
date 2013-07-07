#ProjectRichelBilderbeek

Richel Bilderbeek's work

## What it is

ProjectRichelBilderbeek consists of:
* A collection of console, desktop (Qt and VCL) and web (Wt) applications
* A desktop application called ProjectRichelBilderbeekDesktop (in Projects) containing the bundled (Qt) desktop applications
* A web application called ProjectRichelBilderbeekWebsite (in Projects) containing the bundled (Wt) web applications
* A console application called ProjectRichelBilderbeekConsole (in Projects) containing the bundled console applications
* C++ Builder Windows-only code, to be ported to cross-platform Qt Creator code
* The core of Richel Bilderbeek's HTML website

## Where to start

The main .pro files are
* /Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pro: contains the bundled (Qt) desktop applications
* /Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekWebsite.pro: contains the bundled (Wt) web applications
* /Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekConsole.pro: contains the bundled console applications

If one of these fails to compile, please let me know (and yes, I have setting up a build server on my todo list).

## What it is not

ProjectRichelBilderbeek does not include:
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

These libraries are added to allow easy crosscompilation to Windows using the often-supplied 'crosscompile.sh' scripts. 
For crosscompiling from Lubuntu to Windows I use [MXE](https://github.com/mxe/mxe).

## Git policy

I follow the branching policy from [this article](http://nvie.com/posts/a-successful-git-branching-model), using only
three types: master, develop and feature branches.
* After every push to the master branch, ProjectRichelBilderbeek* must all compile
* Only the develop branch pushes to master
* The feature branch branches and merges with the develop branch

## External links

* [Richel Bilderbeek's HTML webpage](http://www.richelbilderbeek.nl)
