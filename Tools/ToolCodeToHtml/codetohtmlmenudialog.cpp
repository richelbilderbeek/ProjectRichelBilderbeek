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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "codetohtmlmenudialog.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#include <boost/scoped_ptr.hpp>

#include "codetohtml.h"
#include "fileio.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "codetohtmldialog.h"
#include "codetohtmltechinfotype.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::CodeToHtmlMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  #ifndef NDEBUG
  assert(argc > 0);
  assert(ribi::fileio::IsRegularFile(argv[0]));
  assert(ribi::fileio::IsFolder(ribi::fileio::GetPath(argv[0])));
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

  std::string page_type_str { "cpp" };
  std::string content_type_str { "cpp" };
  std::string tech_info_str { "yes" };

  std::string source;

  ///Find page type
  if (std::count(v.begin(),v.end(),std::string("--page_type")))
  {
    const int index
      = std::distance(v.begin(),std::find(v.begin(),v.end(),std::string("--page_type")));
    assert(index < static_cast<int>(v.size()));
    if (index == static_cast<int>(v.size() - 1))
    {
      std::cout
        << "Please supply an argument after --page_type.\n"
        << "\n"
        << "For example:"
        << "  " << argv[0] << " --source main.cpp --page_type cpp\n";
      return 1;
    }
    page_type_str = v[index + 1];
  }

  //Check page_type parameter
  {
    if (!c2h::CanStrToPageType(page_type_str))
    {
      std::cout << "Parameter 'page_type' set to incorrect value of '" << page_type_str << "'\n";
      std::cout << "Possible values:\n";
      const std::vector<c2h::PageType> v = c2h::GetAllPageTypes();
      std::transform(
        v.begin(),
        v.end(),
        std::ostream_iterator<std::string>(std::cout,"\n"),
        [](const c2h::PageType t)
        {
          return c2h::PageTypeToStr(t);
        }
      );
      std::cout
        << "\n"
        << "Example:"
        << "  " << argv[0] << " --source main.cpp --page_type cpp\n";
      return 1;
    }
  }
  std::cout << "Page type: '" << page_type_str << "' (OK)" << std::endl;

  ///Find content_type
  if (std::count(v.begin(),v.end(),std::string("--content_type")))
  {
    const int index
      = std::distance(v.begin(),std::find(v.begin(),v.end(),std::string("--content_type")));
    assert(index < static_cast<int>(v.size()));
    if (index == static_cast<int>(v.size() - 1))
    {
      std::cout
        << "Please supply an argument after --content_type.\n"
        << "\n"
        << "For example:"
        << "  " << argv[0] << " --source main.cpp --content_type cpp\n";
      return 1;
    }
    content_type_str = v[index + 1];
  }

  //Check content_type parameter
  {
    if (!c2h::CanStrToContentType(content_type_str))
    {
      std::cout << "Parameter 'content_type' set to incorrect value of '" << content_type_str << "'\n";
      std::cout << "Possible values:\n";
      const std::vector<c2h::ContentType> v = c2h::GetAllContentTypes();
      std::transform(
        v.begin(),
        v.end(),
        std::ostream_iterator<std::string>(std::cout,"\n"),
        [](const c2h::ContentType t)
        {
          return c2h::ContentTypeToStr(t);
        }
      );
      return 1;
    }
  }
  std::cout << "Content type: '" << content_type_str << "' (OK)" << std::endl;

  ///Find tech_info
  if (std::count(v.begin(),v.end(),std::string("--tech_info")))
  {
    const int index
      = std::distance(v.begin(),std::find(v.begin(),v.end(),std::string("--tech_info")));
    assert(index < static_cast<int>(v.size()));
    if (index == static_cast<int>(v.size() - 1))
    {
      std::cout
        << "Please supply an argument after --tech_info.\n"
        << "\n"
        << "For example:"
        << "  " << argv[0] << " --source main.cpp --tech_info yes\n";
      return 1;
    }
    tech_info_str = v[index + 1];
  }

  //Check tech_info parameter
  {
    if (!c2h::CanStrToTechInfoType(tech_info_str))
    {
      std::cout << "Parameter 'tech_info' set to incorrect value of '" << tech_info_str << "'\n";
      std::cout << "Possible values:\n";
      const std::vector<c2h::TechInfoType> v = c2h::GetAllTechInfoTypes();
      std::transform(
        v.begin(),
        v.end(),
        std::ostream_iterator<std::string>(std::cout,"\n"),
        [](const c2h::TechInfoType t)
        {
          return c2h::TechInfoTypeToStr(t);
        }
      );
      return 1;
    }
  }
  std::cout << "Tech info: '" << tech_info_str << "' (OK)" << std::endl;

  ///Find source
  if (std::count(v.begin(),v.end(),std::string("--source")))
  {
    const int index
      = std::distance(v.begin(),std::find(v.begin(),v.end(),std::string("--source")));
    assert(index < static_cast<int>(v.size()));
    if (index == static_cast<int>(v.size() - 1))
    {
      std::cout
        << "Please supply an argument after --source.\n"
        << "\n"
        << "For example:"
        << "  " << argv[0] << " --source main.cpp\n";
      return 1;
    }
    source = v[index + 1];
  }
  else
  {
    std::cout
      << "Please supply a source.\n"
      << "\n"
      << "For example:"
      << "  " << argv[0] << " --source main.cpp\n";
    return 1;
  }

  std::cout << "Source: '" << source << "'" << std::endl;

  if (!ribi::fileio::IsFolder(source) && !ribi::fileio::IsRegularFile(source))
  {
    std::cout << "Source exists: no\n";
    std::cout << "Specify an existing file or folder\n";
    return 1;
  }
  assert(ribi::fileio::IsFolder(source) || ribi::fileio::IsRegularFile(source));

  std::cout << "Source exists: yes" << std::endl;

  if (ribi::fileio::GetFileBasename(source).empty())
  {
    std::cout
      << "Source its basename has length zero (which can be due to chosing '.' or '..')\n"
      << "Please choose a regular name as a source";
    return 1;
  }


  if (ribi::fileio::IsFolder(source))
  {
    std::cout << "Source is directory: yes" << std::endl;
  }
  else
  {
    assert(ribi::fileio::IsRegularFile(source));
    std::cout << "Source is directory: no" << std::endl;
  }

  assert( (ribi::fileio::IsFolder(source) || ribi::fileio::IsRegularFile(source))
    && "Source can be a file or a path");

  const c2h::PageType page_type = c2h::StrToPageType(page_type_str);
  const c2h::ContentType content_type = c2h::StrToContentType(content_type_str);
  const c2h::TechInfoType tech_info = c2h::StrToTechInfoType(tech_info_str);

  try
  {
    assert( (ribi::fileio::IsFolder(source) || ribi::fileio::IsRegularFile(source))
      && "Source can be a file or a path");

    const boost::scoped_ptr<const c2h::Dialog> c {
      new const c2h::Dialog(
        page_type,
        source,
        content_type,
        tech_info)
    };
    const std::vector<std::string> v = c->ToHtml();
    const std::string output_filename = ribi::fileio::GetFileBasename(source) + ".htm";
    assert(output_filename != std::string(".htm"));
    std::cout << "Output written to '" << output_filename << "'" << std::endl;
    std::ofstream f(output_filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    std::cout << "CodeToHtml succeeded" << std::endl;
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
  return 0;
}

const ribi::About ribi::CodeToHtmlMenuDialog::GetAbout() const noexcept
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


const std::vector<std::string> ribi::CodeToHtmlMenuDialog::GetHelp() const noexcept
{
  return {
    "Allowed options for CodeToHtmlConsole:",
    "",
    "about          displays the 'About' information",
    "page_type      page type (used in header and footer): cpp (*), text. music, tool",
    "help           produce this help message",
    "tech_info      header and footer type: auto, no, yes (*)",
    "source         source of the content: a (.pro) filename or foldername",
    "content_type   content type: cpp",
    "version        displays the version",
    "",
    "Examples:",
    "  CodeToHtmlConsole --source main.cpp",
    "  CodeToHtmlConsole --source MyDocs --tech_info no --content_type txt"
   };
}

const std::string ribi::CodeToHtmlMenuDialog::GetVersion() const noexcept
{
  return "2.10";
}

const std::vector<std::string> ribi::CodeToHtmlMenuDialog::GetVersionHistory() const noexcept
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
    "2013-10-25: version 2.10: console application callable from ProjectRichelBilderbeek"
  };
  return v;
}
