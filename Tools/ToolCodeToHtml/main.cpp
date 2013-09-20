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
#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

#include <QDir>
#include <QFile>
#include <QFileInfoList>

#include "codetohtmldialog.h"
#include "codetohtmlmenudialog.h"
#include "codetohtmltechinfotype.h"
#include "codetohtml.h"
#include "trace.h"
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppGetCurrentFolder.htm
const std::string GetCurrentFolder(const std::string& s)
{
  return c2h::GetPath(s);
}

//From http://www.richelbilderbeek.nl/CppGetFoldersInFolder.htm
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

int main(int argc, char* argv[])
{
  START_TRACE();

  #ifndef NDEBUG
  #ifndef _WIN32
  assert(c2h::IsTidyInstalled());
  #endif
  #else
  assert(1==2 && "I will be deleted");
  #endif

  // Declare the supported options.
  boost::program_options::options_description d("Allowed options for CodeToHtmlConsole");

  std::string page_type_str;
  std::string content_type_str;
  std::string tech_info_str;

  std::string source;

  d.add_options()
      ("about","displays the 'About' information")
      ("page_type",
         boost::program_options::value<std::string>(&page_type_str)->default_value("cpp"),
         "page type (used in header and footer)")
      ("help","produce this help message")
      ("tech_info",
         boost::program_options::value<std::string>(&tech_info_str)->default_value("yes"),
         "Header and footer type: auto, no, yes")
      ("source",
         boost::program_options::value<std::string>(&source),
         "Source of the content: a (.pro) filename or foldername")
      ("content_type",
         boost::program_options::value<std::string>(&content_type_str)->default_value("cpp"),
         "content type")
      ("version","displays the version")
       ;

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  if (m.count("help"))
  {
    std::cout << d << "\n";
    return 0;
  }

  if (m.count("about"))
  {
    std::cout << ribi::CodeToHtmlMenuDialog::GetAbout() << "\n";
    return 0;
  }

  if (m.count("version"))
  {
    std::cout << ribi::CodeToHtmlMenuDialog::GetVersion() << "\n";
    return 0;
  }

  //Check content_type parameter
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
      return 0;
    }
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

  if (!QFile::exists(source.c_str()))
  {
    std::cout << "Source: " << source << "\n";
    std::cout << "Source exists: no\n";
    std::cout << "Specify an existing file or folder\n";
    return 0;
  }
  //std::cout << "Source exists: yes\n";
  if (c2h::IsFolder(source))
  {
    std::cout << "Source is directory: yes\n";
  }
  else
  {
    assert(c2h::IsRegularFile(source));
    std::cout << "Source is directory: no\n";
  }

  assert( (c2h::IsFolder(source) || c2h::IsRegularFile(source))
    && "Source can be a file or a path");

  const c2h::PageType page_type = c2h::StrToPageType(page_type_str);
  const c2h::ContentType content_type = c2h::StrToContentType(content_type_str);
  const c2h::TechInfoType tech_info = c2h::StrToTechInfoType(tech_info_str);

  //Check for recuriveness
  if (GetFoldersInFolder(source).empty())
  {
    std::cout << "Non-recursive conversion\n";

    assert( (c2h::IsFolder(source) || c2h::IsRegularFile(source))
      && "Source can be a file or a path");

    c2h::Dialog c(page_type,source,content_type,tech_info);
    const std::vector<std::string> v = c.ToHtml();
    const std::string output_filename = c2h::GetFileBasename(source) + ".htm";
    std::ofstream f(output_filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  else
  {
    std::cout << "Recursive conversion\n";

    assert( (c2h::IsFolder(source) || c2h::IsRegularFile(source))
      && "Source can be a file or a path");

    const std::vector<std::string> folders = GetFoldersInFolder(source);
    for(const std::string& folder: folders)
    {
      const std::string folder_full_path = source + "/" + folder;
      TRACE(folder);
      TRACE(folder_full_path);
      c2h::Dialog c(page_type,folder_full_path,content_type,tech_info);
      const std::vector<std::string> v = c.ToHtml();
      const std::string output_filename = c2h::GetFileBasename(folder_full_path) + ".htm";
      std::ofstream f(output_filename.c_str());
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }
  }
  std::cout << "CodeToHtml succeeded" << std::endl;
}
