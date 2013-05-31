//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "createqtprojectzipfilepath.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>

#include "trace.h"

namespace CreateQtProjectZipFile {

Path::Path(const std::string& s)
  : m_filename(ExtractFilename(s)),
    m_main_folder(ExtractMainFolder(s)),
    m_sub_folder(ExtractSubFolder(s))
{
  #ifndef NDEBUG
  Path::Test();
  #endif
}

Path::Path(const std::string& main_folder,const std::string& sub_folder, const std::string& filename)
  : m_filename(filename),
    m_main_folder(main_folder),
    m_sub_folder(sub_folder)
{
  #ifndef NDEBUG
  Path::Test();
  #endif
}

const std::string Path::ExtractFilename(const std::string& filename)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,filename,
    std::bind2nd(std::equal_to<char>(),'/'),
    boost::algorithm::token_compress_on);
  if (v.size() >= 1) return v[ v.size() - 1];
  else return std::string();
}

const std::string Path::ExtractMainFolder(const std::string& filename)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,filename,
    std::bind2nd(std::equal_to<char>(),'/'),
    boost::algorithm::token_compress_on);
  std::string t = (v.size() >= 3 ? v[ v.size() - 3] : std::string());
  #ifndef NDEBUG
  if (t=="r") TRACE(filename);
  assert(t!="r");
  #endif
  if (t=="..") t = std::string();
  if (t=="fparser4.5.1") return "Libraries/fparser4.5.1";
  return t;
}

const std::string Path::ExtractSubFolder(const std::string& filename)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,filename,
    std::bind2nd(std::equal_to<char>(),'/'),
    boost::algorithm::token_compress_on);
  std::string t = (v.size() >= 2 ? v[ v.size() - 2] : std::string());
  #ifndef NDEBUG
  if (t=="r") TRACE(filename);
  assert(t!="r");
  #endif
  if (t=="..") t = std::string();
  return t;
}

bool Path::IsComplete() const
{
  return !m_main_folder.empty()
      && !m_sub_folder.empty()
      && !m_filename.empty();
}

bool Path::IsPresent() const
{
  const std::string path = std::string("../../") + ToStr();
  //TRACE(path);
  return boost::filesystem::is_regular_file(path);
}

void Path::SetMainFolder(const std::string& s)
{
  m_main_folder = s;
}

void Path::SetSubFolder(const std::string& s)
{
  m_sub_folder = s;
}

void Path::Test()
{
  //Test exactly once
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    const Path p("home/richel/x/y/z.txt");
    assert(p.GetMainFolder() == "x");
    assert(p.GetSubFolder() == "y");
    assert(p.GetFilename() == "z.txt");
    assert(p.ToStr() == "x/y/z.txt");
  }
  {
    const Path p("x","y","z.txt");
    assert(p.GetMainFolder() == "x");
    assert(p.GetSubFolder() == "y");
    assert(p.GetFilename() == "z.txt");
    assert(p.ToStr() == "x/y/z.txt");
  }
}

const std::string Path::ToStr() const
{
  return m_main_folder + "/" + m_sub_folder + "/" + m_filename;
}

} //~namespace CreateQtProjectZipFile

