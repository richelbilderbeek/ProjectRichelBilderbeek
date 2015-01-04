//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "codetohtmlmenudialog.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/scoped_ptr.hpp>

#include "codetohtml.h"
#include "codetohtmldialog.h"
#include "codetohtmlinfo.h"
#include "fileio.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::c2h::CodeToHtmlMenuDialog::CodeToHtmlMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::c2h::CodeToHtmlMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  #ifndef NDEBUG
  assert(argc > 0);
  assert(ribi::fileio::FileIo().IsRegularFile(argv[0]));
  assert(ribi::fileio::FileIo().IsFolder(ribi::fileio::FileIo().GetPath(argv[0])));
  #ifndef _WIN32
  assert(c2h::IsTidyInstalled());
  #endif
  #else
  std::cout << "Starting " << argv[0] << std::endl;
  assert(1==2 && "I will be deleted");
  #endif

  std::vector<std::string> v;
  for (int i=1; i!=argc; ++i) { v.push_back(argv[i]); }
  std::cout << "Number of arguments supplied: " << (argc-1) << std::endl;

  if (argc == 1)
  {
    std::cout
      << "Please supply a source.\n"
      << "\n"
      << "For example:"
      << "  CodeToHtml main.cpp\n";
    return 1;
  }
  if (argc > 2)
  {
    std::cout
      << "Please supply exactly one argument: the source folder or file.\n"
      << "\n"
      << "For example:"
      << "  CodeToHtml main.cpp\n";
    return 1;
  }
  const std::string source = argv[1];
  std::cout << "Source: '" << source << "'" << std::endl;

  if (!ribi::fileio::FileIo().IsFolder(source) && !ribi::fileio::FileIo().IsRegularFile(source))
  {
    std::cout << "Source exists: no\n";
    std::cout << "Specify an existing file or folder\n";
    return 1;
  }
  assert(ribi::fileio::FileIo().IsFolder(source) || ribi::fileio::FileIo().IsRegularFile(source));

  std::cout << "Source exists: yes" << std::endl;

  if (ribi::fileio::FileIo().GetFileBasename(source).empty())
  {
    std::cout
      << "Source its basename has length zero (which can be due to chosing '.' or '..')\n"
      << "Please choose a regular name as a source";
    return 1;
  }

  assert( (ribi::fileio::FileIo().IsFolder(source) || ribi::fileio::FileIo().IsRegularFile(source))
    && "Source can be either a file or a path");


  if (ribi::fileio::FileIo().IsFolder(source))
  {
    std::cout << "Source is directory: yes" << std::endl;
  }
  else
  {
    assert(ribi::fileio::FileIo().IsRegularFile(source));
    std::cout << "Source is directory: no" << std::endl;
  }

  const std::function<const std::vector<std::string>(const Dialog*, const std::string&)> f {
      ribi::fileio::FileIo().IsRegularFile(source)
    ? &Dialog::FileToHtml
    : &Dialog::FolderToHtml
  };
  Dialog d;

  try
  {
    const std::vector<std::string> v = f(&d,source);
    const std::string output_filename = ribi::fileio::FileIo().GetFileBasename(source) + ".htm";
    assert(output_filename != ".htm");
    std::cout << "Output written to '" << output_filename << "'" << std::endl;
    std::ofstream f(output_filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    std::cout << "CodeToHtml succeeded" << std::endl;
    return 0;
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
    return 2;
  }
  catch (...)
  {
    std::cout << "Unknown exception thrown" << std::endl;
    return 3;
  }
}

ribi::About ribi::c2h::CodeToHtmlMenuDialog::GetAbout() const noexcept
{
  ribi::About a {
    "Richel Bilderbeek",
    "CodeToHtml",
    "tool to convert code to heavily-linked HTML",
    "the 11th of August 2014",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolCodeToHtml.htm",
    GetVersion(),
    GetVersionHistory()
  };
  a.AddLibrary("CodeToHtml (class) version: " + c2h::Info::GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("HTML Tidy for Linux/x86 released on 25 March 2009");
  return a;
}


ribi::Help ribi::c2h::CodeToHtmlMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
    },
    {
      "CodeToHtmlConsole main.cpp",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::c2h::CodeToHtmlMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramCodeToHtml);
  assert(p);
  return p;
}

std::string ribi::c2h::CodeToHtmlMenuDialog::GetVersion() const noexcept
{
  return "3.3";
}

std::vector<std::string> ribi::c2h::CodeToHtmlMenuDialog::GetVersionHistory() const noexcept
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
    "2013-09-26: version 2.9: use of boost::checked_delete on all classes, removed use of Boost.Program_options"
    "2013-10-25: version 2.10: console application callable from ProjectRichelBilderbeek",
    "2013-11-26: version 3.0: improved interface and architecture, support for OpenFOAM projects",
    "2014-04-27: version 3.1: prevents huge HTML file creation",
    "2014-07-16: version 3.2: 4000 replacements, increased use of C++11, link std::x to CppStdX.htm",
    "2014-08-11: version 3.3: increased use of TDD"
  };
  return v;
}

#ifndef NDEBUG
void ribi::c2h::CodeToHtmlMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    { boost::shared_ptr<c2h::Info> info(new c2h::Info); }
    try { QrcFile(""); } catch(std::logic_error&) { /* OK */ };
    try {  boost::shared_ptr<QtCreatorProFile> p{new QtCreatorProFile("")}; } catch(std::logic_error&) { /* OK */ };
    ribi::c2h::Dialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const boost::shared_ptr<const c2h::Info> info(new c2h::Info);
    const std::vector<std::string> html {
      info->ToHtml("non_existing_page_762538762539827382309728")
    };
    assert(html.size() == 1);
    const std::string no_info_str = "<!-- No CodeToHtmlInfo about this class";
    const std::string html_str = html[0];
    assert(html_str.substr(0,no_info_str.size()) == no_info_str);
  }
}
#endif

void ribi::c2h::CodeToHtmlMenuDialog::TestAllProgramsHaveInfo() noexcept
{
  //Every Program must have some CodeToHtml info
  const std::vector<boost::shared_ptr<Program> > programs { Program::GetAllPrograms() };
  std::vector<std::string> pagenames;
  std::transform(programs.begin(),programs.end(),std::back_inserter(pagenames),
    [](const boost::shared_ptr<Program> program)
    {
      const std::string s = program->GetUrl();
      assert(s.substr(s.size() - 4, 4) == ".htm");
      const std::string t = s.substr(0,s.size() - 4);
      return t;
    }
  );

  for (const std::string pagename: pagenames)
  {
    const boost::shared_ptr<const c2h::Info> info(new c2h::Info);
    const std::vector<std::string> html {
      info->ToHtml(pagename)
    };
    assert(!html.empty());
    const std::string no_info_str = "<!-- No CodeToHtmlInfo about this class";
    const std::string html_str = html[0];
    if(html_str.substr(0,no_info_str.size()) == no_info_str)
    {
      TRACE("ERROR");
      TRACE("No info for page:");
      TRACE(pagename);
    }
    assert(html_str.substr(0,no_info_str.size()) != no_info_str
      && "For every programType there must be HTML info");
  }
}
