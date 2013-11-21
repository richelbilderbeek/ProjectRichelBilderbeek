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
#include "codetohtml.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <boost/scoped_ptr.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <QDir>
#include <QFile>

#include "codetohtmlcontent.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlsnippettype.h"
#include "codetohtmltechinfo.h"
#include "fileio.h"
#include "qtcreatorprofile.h"
#include "qtcreatorprofilezipscript.h"
#include "trace.h"

#pragma GCC diagnostic pop

#ifndef _WIN32
bool ribi::c2h::IsCleanHtml(const std::vector<std::string>& html)
{
  assert(IsTidyInstalled());

  const std::string temp_filename = "tmp.htm";
  const std::string temp_filename_tidy = "tmp_codetohtmldialog_test_tidy.txt";

  //Remove previous HTML file
  {
    std::remove(temp_filename.c_str());
    assert(!ribi::fileio::IsRegularFile(temp_filename));
  }
  //Write HTML to file
  {
    std::ofstream f(temp_filename.c_str());
    std::copy(html.begin(),html.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  //Start tidy, creates output file
  {
    assert(ribi::fileio::IsRegularFile(temp_filename));
    const std::string command = "tidy -q -e -f " + temp_filename_tidy + " " + temp_filename;
    const int error = std::system(command.c_str());
    /*
    if (error && html[5] != std::string(" <title>XXX</title>"))
    {
      TRACE("Dear assert, check tmp.htm, as this is the HTML tidy failed on");
      TRACE(command);
      TRACE(error);
      #ifndef NDEBUG
      for (const std::string& s: FileToVector(temp_filename_tidy))
      {
        TRACE(s);
      }
      #endif
      assert(!error || html[5] != std::string(" <title>XXX</title>");
      return false;
    }
    assert(!error);
    assert(IsRegularFile(temp_filename_tidy));
    */
    if (error) return false;
  }
  const auto v = ribi::fileio::FileToVector(temp_filename_tidy);

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
bool ribi::c2h::IsTidyInstalled()
{
  const std::string temp_filename_tidy = "tmp_tidy_output.txt";

  std::remove(temp_filename_tidy.c_str());
  assert(!ribi::fileio::IsRegularFile(temp_filename_tidy));

  //'2>' denotes -AFAIK- 'Write to file only, no screen output'
  const std::string command = "tidy -v 2> ./" + temp_filename_tidy;
  const int error = std::system(command.c_str());
  //assert(ok == 0 && "While I know I have tidy installed");
  //assert(IsRegularFile(temp_filename_tidy) && "While I know I have tidy installed");
  if (!ribi::fileio::IsRegularFile(temp_filename_tidy)) return false;

  std::remove(temp_filename_tidy.c_str());
  assert(!ribi::fileio::IsRegularFile(temp_filename_tidy));

  return !error;
}
#endif

const std::vector<std::string> ribi::c2h::GetProFilesInFolder(
  const std::string& folder)
{
  return ribi::fileio::GetFilesInFolderByRegex(folder,".*\\.(pro)\\>");
}

#ifndef NDEBUG
void ribi::c2h::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
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
        "a.pri",
        "b.pri",
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

  //GetProFiles
  {
    //Always first remove the temp file
    std::remove("tmp23465278.pro");

    const std::size_t n = GetProFilesInFolder("").size();
    {
      std::ofstream f("tmp23465278.pro");
      f << "tmp";
      f.close();
    }
    const std::size_t p = GetProFilesInFolder("").size();
    if (n != p - 1)
    {
      TRACE(n);
      TRACE(p);
      for (std::string s: GetProFilesInFolder("")) TRACE(s);
    }
    assert(n == p - 1);
    std::remove("tmp23465278.pro");
    const std::size_t q = GetProFilesInFolder("").size();
    assert(n == q);
  }
}
#endif

const std::vector<std::string> ribi::c2h::ConvertCodeSnippet(
  const std::vector<std::string>& code,
  const SnippetType snippet_type)
{
  FileType file_type = FileType::other;
  switch (snippet_type)
  {
    case SnippetType::cpp : file_type = FileType::cpp; break;
    case SnippetType::text: file_type = FileType::txt; break;
  }

  const boost::shared_ptr<File> file(new File(code,file_type));
  return file->GetHtml();
}

const std::vector<std::string> ribi::c2h::ConvertFile(
  const std::string& filename,
  const FileType content_type)
{
  const std::vector<std::string> v {
    ribi::fileio::FileToVector(filename)
  };
  const boost::shared_ptr<File> content(new File(filename,v,content_type));
  return content->GetHtml();
}

const std::vector<std::string> ribi::c2h::ConvertFiles(const std::string& foldername)
{
  std::vector<std::string> v;
  {
    const std::vector<std::string> files = GetSortedFilesInFolder(foldername);
    std::copy(files.begin(),files.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    for(const std::string& filename: files)
    {
      const std::string filename_full = foldername + "/" + filename;
      assert(ribi::fileio::IsRegularFile(filename_full));
      const boost::shared_ptr<File> content {
        new File(
          filename,
          ribi::fileio::FileToVector(filename_full)
        )
      };
      const std::vector<std::string> w = content->GetHtml();
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
  }
  return v;
}

const std::vector<std::string> ribi::c2h::ConvertFolder(
  const std::string& foldername,
  const PageType page_type)
{
  std::vector<std::string> v;
  {
    const boost::shared_ptr<Header> h {
      new Header(
        page_type,
        ribi::fileio::GetFileBasename(foldername))
    };
    const std::vector<std::string> w = h->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    const std::vector<std::string> pro_files {
      GetProFilesInFolder(foldername)
    };
    #ifndef NDEBUG
    for (const std::string& pro_file: pro_files) { assert(ribi::fileio::IsRegularFile(pro_file)); }
    #endif

    const boost::shared_ptr<TechInfo> techInfo(new TechInfo(pro_files));
    const std::vector<std::string> w = techInfo->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    const std::vector<std::string> files = GetSortedFilesInFolder(foldername);
    std::copy(files.begin(),files.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        const boost::shared_ptr<File> content {
          new File(
            filename,
            ribi::fileio::FileToVector(filename))
        };
        const std::vector<std::string> w = content->GetHtml();
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

const std::vector<std::string> ribi::c2h::ConvertProject(const std::string& filename)
{
  assert(ribi::fileio::GetExtension(filename) == ".pro");
  boost::shared_ptr<ribi::QtCreatorProFile> pro_file(new ribi::QtCreatorProFile(filename));

  std::vector<std::string> v;
  {
    const boost::shared_ptr<Header> h {
      new Header(
        PageType::cpp,
        ribi::fileio::GetFileBasename(filename)
      )
    };
    const std::vector<std::string> w = h->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    assert(ribi::fileio::IsRegularFile(filename));
    boost::shared_ptr<TechInfo> i(new TechInfo( { filename } ));
    const std::vector<std::string> w = i->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Obtain all files with a full path
  {
    const boost::shared_ptr<ribi::QtCreatorProFileZipScript> script(
      new ribi::QtCreatorProFileZipScript(pro_file));

    const auto files = script->GetFilenames();
    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        const boost::scoped_ptr<const File> content {
          new File(
            filename,
            ribi::fileio::FileToVector(filename)
          )
        };
        const std::vector<std::string> w = content->GetHtml();
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





const std::vector<std::string> ribi::c2h::GetSortedFilesInFolder(const std::string& folder)
{
  std::vector<std::string> files {
    FilterFiles(
      ribi::fileio::GetFilesInFolder(folder)
    )
  };
  files = SortFiles(files);
  return files;
}

const std::vector<std::string> ribi::c2h::FilterFiles(const std::vector<std::string>& files)
{
  std::vector<std::string> v;
  std::copy_if(files.begin(), files.end(),std::back_inserter(v),
    [](const std::string& file)
    {
      const std::string ext = ribi::fileio::GetExtension(file);
      return
           ext == ".c"
        || ext == ".cpp"
        || ext == ".h"
        || ext == ".hpp"
        || ext == ".pri"
        || ext == ".pro"
        || ext == ".py"
        || ext == ".sh";
    }
  );
  return v;
}


const std::vector<std::string> ribi::c2h::SortFiles(std::vector<std::string> files)
{
  std::sort(files.begin(), files.end(),
    [](const std::string& lhs,const std::string& rhs)
    {
      const std::string lhs_base = ribi::fileio::GetFileBasename(lhs);
      const std::string rhs_base = ribi::fileio::GetFileBasename(rhs);
      const std::string lhs_ext = ribi::fileio::GetExtension(lhs);
      const std::string rhs_ext = ribi::fileio::GetExtension(rhs);
      static const std::string pro(".pro");
      static const std::string pri(".pri");
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

      //.pri files then
      if (lhs_ext == pri)
      {
        if (rhs_ext == pro) //.pro first
        {
          return false;
        }
        if (rhs_ext == pri) //sort .pri files
        {
          return lhs_base < rhs_base;
        }
        if (rhs_ext != pri) //else .pri is second
        {
          return true;
        }
      }

      //Headers then
      if (lhs_ext == h && rhs_ext == cpp && lhs_base == rhs_base)
      {
        return true;
      }
      //Pri before unit files
      if ( (lhs_ext == h || lhs_ext == cpp) && rhs_ext == pri)
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
