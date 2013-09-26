//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "codetohtmlmenudialog.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "trace.h"
#pragma GCC diagnostic pop

const ribi::About ribi::CodeToHtmlMenuDialog::GetAbout() noexcept
{
  ribi::About a {
    "Richel Bilderbeek",
    "CodeToHtml",
    "tool to convert code to heavily-linked HTML",
    "the 17th of September 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/ToolCodeToHtml.htm",
    GetVersion(),
    GetVersionHistory()
  };
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::CodeToHtmlMenuDialog::GetVersion() noexcept
{
  return "2.8";
}

const std::vector<std::string> ribi::CodeToHtmlMenuDialog::GetVersionHistory() noexcept
{
  const std::vector<std::string> v {
    "2010-03-14: version 1.0: programmed initial console version of CodeToHtml. Due to my switch from Windows to Ubuntu, I had to abandon MS Word as my favorite HTML editor. Then I had to write my webpages in plain HTML, but adding links to all my code snippets was tiresome. CodeToHtml automated this for me",
    "2010-04-10: version 1.1: cleaned up code, about 200 replacement entries",
    "2010-05-07: version 1.2: about 650 replacement entries",
    "2010-07-24: version 1.3: about 800 replacement entries",
    "2010-07-24: version 1.4: made a GUI version of CodeToHtml",
    "2010-07-25: version 1.5: added a save button, removed some useless code (like 'createCss'), improved visual appearance",
    "2010-08-07: version 1.6: added the option to convert multiple C++ files to one single page",
    "2010-08-09: version 1.7: also put the .pro files in the website generated from file. Also fix that long lines of (plaintext)code got multiplied in the HTML output",
    "2010-09-24: version 1.8: added 'About' and 'What's New' screen, changed GUI, added posibility to convert text to HTML",
    "2010-09-24: version 1.9: posibility to only convert text body",
    "2010-10-02: version 1.10: added use of pictograms",
    "2010-10-08: version 1.11: added important new links, renamed pictogram names",
    "2010-11-18: version 1.12: obtain just-read version numbers of Qt and Ubuntu",
    "2010-12-12: version 1.13: added creation of tool and music pages",
    "2010-12-18: version 1.14: fixed error in calling sylesheet",
    "2010-12-19: version 1.15: support of displaying multiple Qt Creator project files in project conversion",
    "2010-12-22: version 1.16: display the number of text replacements in the About screen",
    "2011-01-15: version 1.17: switched to C++0x standard, replaced DialogAbout",
    "2011-01-30: version 1.18: 1900 replacement, added the Android, Maemo, Symbian, VirtualBox operating systems",
    "2011-04-12: version 1.19: +2300 replacement, slightly improved code",
    "2011-04-14: version 1.20: major architectural change for future Wt support and increased speed, changed OS to Lubuntu",
    "2011-06-26: version 1.21: seperated \'Convert Project\' logic from GUI, also converts .sh files",
    "2011-07-01: version 1.22: added all Wt classes",
    "2011-07-11: version 1.23: added all C++0x algorithms",
    "2011-09-11: version 1.24: added console version, major architectural change",
    "2011-09-15: version 2.0: major achitectureal change, added command-line and web version",
    "2012-08-06: version 2.1: added replacements, improved GUI of desktop version",
    "2012-08-07: version 2.2: let the technical information be collected from the project file",
    "2012-10-30: version 2.3: replaced C++0x by C++11, obtain the Qt Creator version automatically",
    "2012-12-22: version 2.4: HTML produced is checked by 'tidy', many minor improvements",
    "2013-05-19: version 2.5: +3400 replacements, following architectural changes in QtCreatorProFile and QtCreatorProFileZipScript",
    "2013-08-19: version 2.6: replaced Boost.Filesystem and Boost.Regex by Qt and Boost.Xpressive, added tests, added +5000 lines of CodeToHtml info",
    "2013-09-05: version 2.7: transition to namespace ribi",
    "2013-09-17: version 2.8: compile with -Weffc++, fixed bug due to this, removed recursive replacements, cleaned info, do tests at run-time, added reading .pri files"
    "2013-09-26: version 2.9: use of boost::checked_delete on all classes"
  };
  return v;
}
