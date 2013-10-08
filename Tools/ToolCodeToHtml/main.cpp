//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2011  Richel Bilderbeek

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
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

//#include <boost/program_options.hpp>

#include <QDir>
#include <QFile>
#include <QFileInfoList>

#include "codetohtmldialog.h"
#include "codetohtml.h"
#include "codetohtmlinfo.h"
#include "codetohtmlmenudialog.h"
#include "codetohtmltechinfotype.h"
#include "trace.h"
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppGetCurrentFolder.htm
const std::string GetCurrentFolder(const std::string& s)
{
  return c2h::GetPath(s);
}

//From http://www.richelbilderbeek.nl/CppGetFoldersInFolder.htm
/*
const std::vector<std::string> GetFoldersInFolder(const std::string& folder)
{
  //Obtain all folders
  QDir dir(folder.c_str());
  dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
  const QFileInfoList list = dir.entryInfoList();

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const int size = list.size();
  for (int i = 0; i != size; ++i)
  {
    v.push_back(list.at(i).fileName().toStdString());
  }
  return v;
}
*/

int main(int argc, char* argv[])
{
  START_TRACE();

  #ifndef NDEBUG
  assert(argc > 0);
  assert(c2h::IsRegularFile(argv[0]));
  assert(c2h::IsFolder(c2h::GetPath(argv[0])));
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

  if ( std::count(v.begin(),v.end(),std::string("help"))
    || std::count(v.begin(),v.end(),std::string("--help"))
    )
  {
    const auto v = ribi::CodeToHtmlMenuDialog::GetHelp();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }

  if ( std::count(v.begin(),v.end(),std::string("about"))
    || std::count(v.begin(),v.end(),std::string("--about"))
    )
  {
    std::cout << ribi::CodeToHtmlMenuDialog::GetAbout() << "\n";

    std::cout
      << "\n"
      << "Source code built on "
      << __DATE__
      << " "
      << __TIME__
      << " ("
    #ifdef NDEBUG
      << "release"
    #else
      << "debug"
    #endif
      << " version)"
      << std::endl;

    return 0;
  }

  if ( std::count(v.begin(),v.end(),std::string("version"))
    || std::count(v.begin(),v.end(),std::string("--version"))
    )
  {
    std::cout << ribi::CodeToHtmlMenuDialog::GetVersion() << "\n";
    return 0;
  }

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
      return 0;
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
      return 0;
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
      return 0;
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
      return 0;
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
      return 0;
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
      return 0;
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
      return 0;
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
    return 0;
  }

  std::cout << "Source: '" << source << "'" << std::endl;

  if (!c2h::IsFolder(source) && !c2h::IsRegularFile(source))
  {
    std::cout << "Source exists: no\n";
    std::cout << "Specify an existing file or folder\n";
    return 0;
  }
  assert(c2h::IsFolder(source) || c2h::IsRegularFile(source));

  std::cout << "Source exists: yes" << std::endl;

  if (c2h::IsFolder(source))
  {
    std::cout << "Source is directory: yes" << std::endl;
  }
  else
  {
    assert(c2h::IsRegularFile(source));
    std::cout << "Source is directory: no" << std::endl;
  }

  assert( (c2h::IsFolder(source) || c2h::IsRegularFile(source))
    && "Source can be a file or a path");

  const c2h::PageType page_type = c2h::StrToPageType(page_type_str);
  const c2h::ContentType content_type = c2h::StrToContentType(content_type_str);
  const c2h::TechInfoType tech_info = c2h::StrToTechInfoType(tech_info_str);

  try
  {
    assert( (c2h::IsFolder(source) || c2h::IsRegularFile(source))
      && "Source can be a file or a path");

    const boost::scoped_ptr<const c2h::Dialog> c {
      new const c2h::Dialog(
        page_type,
        source,
        content_type,
        tech_info)
    };
    const std::vector<std::string> v = c->ToHtml();
    const std::string output_filename = c2h::GetFileBasename(source) + ".htm";
    std::cout << "Output written to '" << output_filename << "'" << std::endl;
    std::ofstream f(output_filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    std::cout << "CodeToHtml succeeded" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Unknown exception thrown" << std::endl;
  }
}
