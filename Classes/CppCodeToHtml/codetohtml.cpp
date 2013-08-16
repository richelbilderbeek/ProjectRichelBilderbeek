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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "codetohtml.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <QDir>

#include "codetohtmlcontent.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlpagetype.h"
#include "codetohtmltechinfo.h"
#include "qtcreatorprofile.h"
#include "qtcreatorprofilezipscript.h"
#include "trace.h"

#pragma GCC diagnostic pop

namespace c2h {

#ifndef _WIN32
bool IsCleanHtml(const std::vector<std::string>& html)
{
  assert(IsTidyInstalled());

  const std::string temp_filename = "tmp.htm";
  const std::string temp_filename_tidy = "tmp_codetohtmldialog_test_tidy.txt";

  //Remove previous HTML file
  {
    std::remove(temp_filename.c_str());
    assert(!IsRegularFile(temp_filename));
  }
  //Write HTML to file
  {
    std::ofstream f(temp_filename.c_str());
    std::copy(html.begin(),html.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  //Start tidy, creates output file
  {
    assert(IsRegularFile(temp_filename));
    const std::string command = "tidy -q -e -f " + temp_filename_tidy + " " + temp_filename;
    const int error = std::system(command.c_str());
    if (error)
    {
      TRACE(command);
      TRACE(error);
      #ifndef NDEBUG
      for (const std::string& s: FileToVector(temp_filename_tidy))
      {
        TRACE(s);
      }
      #endif
      assert(!error);
      return false;
    }
    assert(!error);
    assert(IsRegularFile(temp_filename_tidy));
  }
  const auto v = FileToVector(temp_filename_tidy);

  std::remove(temp_filename.c_str());
  std::remove(temp_filename_tidy.c_str());

  assert(!v.empty());
  if (v.size() > 1 || !v[0].empty())
  {
    TRACE("Errors found by Tidy:");
    const int sz = v.size();
    for (int i=0; i!=sz; ++i)
    {
      TRACE(v[i]);
    }
    return false;
  }
  return true;
}
#endif

#ifndef _WIN32
bool IsTidyInstalled()
{
  const std::string temp_filename_tidy = "tmp_tidy_output.txt";

  std::remove(temp_filename_tidy.c_str());
  assert(!IsRegularFile(temp_filename_tidy));

  //'2>' denotes -AFAIK- 'Write to file only, no screen output'
  const std::string command = "tidy -v 2> " + temp_filename_tidy;
  const int error = std::system(command.c_str());
  //assert(ok == 0 && "While I know I have tidy installed");
  //assert(IsRegularFile(temp_filename_tidy) && "While I know I have tidy installed");
  if (!IsRegularFile(temp_filename_tidy)) return false;

  std::remove(temp_filename_tidy.c_str());
  assert(!IsRegularFile(temp_filename_tidy));

  return !error;
}
#endif

#ifndef NDEBUG
void Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test for correct replacements
  {
    const std::vector<std::pair<std::string,std::string> > v = {
      { "C++ Builder", "<a href=\"CppBuilder.htm\">C++ Builder</a>" },
      { "C++11", "<a href=\"Cpp11.htm\">C++11</a>" },
      { "C++0x", "<a href=\"Cpp0x.htm\">C++0x</a>" },
      { "C++", "<a href=\"Cpp.htm\">C++</a>" },
      { "++", "<a href=\"CppOperatorIncrement.htm\">++</a>" },
      { "--", "<a href=\"CppOperatorDecrement.htm\">--</a>" }
    };
    std::for_each(v.begin(),v.end(),
      [](const std::pair<std::string,std::string>& p)
      {
        const std::string& s = p.first;
        const std::string t = Content::MultiReplace(s,Content::GetReplacementsCpp().Get());
        if (t != p.second)
        {
          TRACE(s);
          TRACE(t);
          TRACE(p.second);
        }
        assert(t == p.second);
      }
    );
  }
  //Test SortedFiles
  {
    const std::vector<std::string> result
      =
      {
        "a.pro",
        "b.pro",
        "c.pro",
        "d.pro",
        "e.pro",
        "a.h",
        "a.cpp",
        "b.h",
        "b.cpp",
        "c.h",
        "c.cpp",
        "d.h",
        "d.cpp",
        "e.h",
        "e.cpp",
        "a.sh",
        "b.sh",
        "c.sh",
        "d.sh",
        "e.sh"
      };
    std::vector<std::string> v = result;
    v.push_back("x.txt"); //Should not be added
    v.push_back("y.txt"); //Should not be added
    std::random_shuffle(v.begin(),v.end());
    v = SortFiles(FilterFiles(v));
    assert(v == result);
  }
  //GetFileBasename
  {
    assert(GetFileBasename("") == std::string(""));
    assert(GetFileBasename("tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder\\tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder/tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder/tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder\\tmp.txt") == std::string("tmp"));
  }
  //GetPath
  {
    assert(GetPath("C:\\any_path\\any_file.cpp")=="C:\\any_path");
    assert(GetPath("/any_path/any_file.cpp")=="/any_path");
  }
}
#endif

const std::vector<std::string> ConvertCodeSnippet(
  const std::vector<std::string>& code,
  const ContentType content_type)
{

  const boost::shared_ptr<Content> content(new Content("",code,content_type));
  return content->ToHtml();
}

const std::vector<std::string> ConvertFile(
  const std::string& filename,
  const ContentType content_type)
{
  const std::vector<std::string> v = FileToVector(filename);
  const boost::shared_ptr<Content> content(new Content(filename,v,content_type));
  return content->ToHtml();
}

const std::vector<std::string> ConvertFiles(const std::string& foldername)
{
  std::vector<std::string> v;
  {
    const std::vector<std::string> files = GetSortedFilesInFolder(foldername);
    std::copy(files.begin(),files.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        const boost::shared_ptr<Content> content(new Content(filename,FileToVector(filename)));
        const std::vector<std::string> w = content->ToHtml();
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    );
  }
  return v;
}

const std::vector<std::string> ConvertFolder(
  const std::string& foldername,
  const PageType page_type)
{
  std::vector<std::string> v;
  {
    const boost::shared_ptr<Header> h(new Header(page_type,GetFileBasename(foldername)));
    const std::vector<std::string> w = h->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    const boost::shared_ptr<TechInfo> techInfo(new TechInfo(GetFilesInFolder(foldername,".*\\.pro\\z")));
    const std::vector<std::string> w = techInfo->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    const std::vector<std::string> files = GetSortedFilesInFolder(foldername);
    std::copy(files.begin(),files.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        const boost::shared_ptr<Content> content(new Content(filename,FileToVector(filename)));
        const std::vector<std::string> w = content->ToHtml();
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    );
  }
  {
    const boost::shared_ptr<Footer> c(new Footer(page_type));
    const std::vector<std::string> w = c->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

const std::vector<std::string> ConvertProject(const std::string& filename)
{
  assert(GetExtension(filename) == ".pro");
  boost::shared_ptr<QtCreatorProFile> pro_file(new QtCreatorProFile(filename));

  std::vector<std::string> v;
  {
    const boost::shared_ptr<Header> h(new Header(PageType::cpp,GetFileBasename(filename)));
    const std::vector<std::string> w = h->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    boost::shared_ptr<TechInfo> i(new TechInfo( { filename } ));
    const std::vector<std::string> w = i->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Obtain all files with a full path
  {
    const boost::shared_ptr<QtCreatorProFileZipScript> script(
      new QtCreatorProFileZipScript(pro_file));

    const auto files = script->GetFilenames();
    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        const std::vector<std::string> w = Content(filename,FileToVector(filename)).ToHtml();
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    );
  }
  {
    const boost::shared_ptr<Footer> f(new Footer(PageType::cpp));
    const std::vector<std::string> w = f->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

const std::vector<std::string> FileToVector(const std::string& filename)
{
  if (!IsRegularFile(filename))
  {
    TRACE(filename);
  }
  assert(IsRegularFile(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

const std::string GetExtension(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "(.*)?(\\.[A-Za-z]*)" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[2];
  }

  return "";
}

const std::string GetFileBasename(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "((.*)(/|\\\\))?([A-Za-z]*)((\\.)([A-Za-z]*))?" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[4];
  }

  return "";
}

const std::vector<std::string> GetFilesInFolder(const std::string& folder)
{
  QDir dir(folder.c_str());
  dir.setFilter(QDir::Files);
  const QFileInfoList list = dir.entryInfoList();

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const int size = list.size();
  for (int i = 0; i != size; ++i)
  {
    const std::string file_name = list.at(i).fileName().toStdString();
    v.push_back(file_name);
  }
  return v;
}

const std::vector<std::string> GetFilesInFolder(
  const std::string& folder,
  const std::string& regex_str)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex
  const boost::regex regex(regex_str);

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  std::copy_if(v.begin(),v.end(),std::back_inserter(w),
    [regex](const std::string& s) { return boost::regex_match(s,regex); } );

  return w;
}

const std::string GetPath(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

const std::vector<std::string> GetSortedFilesInFolder(const std::string& folder)
{
  std::vector<std::string> files = FilterFiles(GetFilesInFolder(folder));
  files = SortFiles(files);
  return files;
}

const std::vector<std::string> FilterFiles(const std::vector<std::string>& files)
{
  std::vector<std::string> v;
  std::copy_if(files.begin(), files.end(),std::back_inserter(v),
    [](const std::string& file)
    {
      TRACE(file);
      const std::string ext = GetExtension(file);
      return
           ext == ".c"
        || ext == ".cpp"
        || ext == ".h"
        || ext == ".hpp"
        || ext == ".pro"
        || ext == ".py"
        || ext == ".sh";
    }
  );
  TRACE(v.size());
  return v;
}

bool IsRegularFile(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}


const std::vector<std::string> SortFiles(std::vector<std::string> files)
{
  std::sort(files.begin(), files.end(),
    [](const std::string& lhs,const std::string& rhs)
    {
      const std::string lhs_base = GetFileBasename(lhs);
      const std::string rhs_base = GetFileBasename(rhs);
      const std::string lhs_ext = GetExtension(lhs);
      const std::string rhs_ext = GetExtension(rhs);
      static const std::string pro(".pro");
      static const std::string sh(".sh");
      static const std::string h(".h");
      static const std::string cpp(".cpp");
      static const std::string py(".py");
      if (lhs_ext == pro)
      {
        //.pro files first
        if (rhs_ext != pro)
        {
          return true;
        }
        if (rhs_ext == pro)
        {
          return lhs_base < rhs_base;
        }
      }
      //Headers then
      if (lhs_ext == h && rhs_ext == cpp && lhs_base == rhs_base)
      {
        return true;
      }
      //Pro before unit files
      if ( (lhs_ext == h || lhs_ext == cpp) && rhs_ext == pro)
      {
        return false;
      }
      //Unit files before script files
      if ( (lhs_ext == h || lhs_ext == cpp) && rhs_ext == sh)
      {
        return true;
      }
      //Sort unit files alphabeticaly
      if ( (lhs_ext == h || lhs_ext == cpp) && (rhs_ext == h || rhs_ext == cpp) )
      {
        return lhs_base < rhs_base;
      }

      //.py one-but-last
      if (lhs_ext == py)
      {
        if (rhs_ext == sh)
        {
          return true;
        }
        if (rhs_ext != py)
        {
          return false;
        }
        if (rhs_ext == py)
        {
          return lhs_base < rhs_base;
        }
      }


      //.sh last
      if (lhs_ext == sh)
      {
        if (rhs_ext != sh)
        {
          return false;
        }
        if (rhs_ext == sh)
        {
          return lhs_base < rhs_base;
        }
      }
      return false;
    }
  );

  return files;
}

} //~namespace c2h
