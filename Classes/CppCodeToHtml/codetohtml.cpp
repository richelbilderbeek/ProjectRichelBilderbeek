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

#include "codetohtmlfile.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlreplacer.h"
#include "testtimer.h"
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

  const std::string temp_filename { fileio::FileIo().GetTempFileName(".htm") };
  const std::string temp_filename_tidy { fileio::FileIo().GetTempFileName("_tidy.txt") };
  assert(!ribi::fileio::FileIo().IsRegularFile(temp_filename));
  //Write HTML to file
  {
    std::ofstream f(temp_filename.c_str());
    std::copy(html.begin(),html.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  //Start tidy, creates output file
  {
    assert(ribi::fileio::FileIo().IsRegularFile(temp_filename));
    const std::string command = "tidy -q -e -f " + temp_filename_tidy + " " + temp_filename;
    const int error = std::system(command.c_str());
    /*
    if (error && html[5] != " <title>XXX</title>")
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
      assert(!error || html[5] != " <title>XXX</title>");
      return false;
    }
    assert(!error);
    assert(IsRegularFile(temp_filename_tidy));
    */
    if (error) return false;
  }
  const auto v = ribi::fileio::FileIo().FileToVector(temp_filename_tidy);


  if (v.size() > 1)
  {
    TRACE("Errors found by Tidy, check the following files:");
    TRACE(temp_filename);
    TRACE(temp_filename_tidy);
    return false;
  }
  fileio::FileIo().DeleteFile(temp_filename.c_str());
  fileio::FileIo().DeleteFile(temp_filename_tidy.c_str());
  return true;
}
#endif

#ifndef _WIN32
bool ribi::c2h::IsTidyInstalled()
{
  const std::string temp_filename_tidy { fileio::FileIo().GetTempFileName() };

  assert(!ribi::fileio::FileIo().IsRegularFile(temp_filename_tidy));

  //'2>' denotes -AFAIK- 'Write to file only, no screen output'
  const std::string command = "tidy -v 2> ./" + temp_filename_tidy;
  const int error = std::system(command.c_str());
  //assert(ok == 0 && "While I know I have tidy installed");
  //assert(IsRegularFile(temp_filename_tidy) && "While I know I have tidy installed");
  if (!ribi::fileio::FileIo().IsRegularFile(temp_filename_tidy)) return false;

  fileio::FileIo().DeleteFile(temp_filename_tidy.c_str());
  assert(!ribi::fileio::FileIo().IsRegularFile(temp_filename_tidy));

  return !error;
}
#endif


#ifndef NDEBUG
void ribi::c2h::Test()
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
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
    v.push_back("x.txt"); //Text files should be filtered away
    v.push_back("y.txt"); //Text files should be filtered away
    std::random_shuffle(std::begin(v),std::end(v));
    v = SortFiles(FilterFiles(v));
    assert(v == result);
  }

}
#endif

std::vector<std::string> ribi::c2h::GetSortedFilesInFolder(const std::string& folder) noexcept
{
  std::vector<std::string> files {
    FilterFiles(
      ribi::fileio::FileIo().GetFilesInFolder(folder)
    )
  };
  files = SortFiles(files);
  return files;
}

std::vector<std::string> ribi::c2h::FilterFiles(const std::vector<std::string>& files) noexcept
{
  std::vector<std::string> v;
  std::copy_if(files.begin(), files.end(),std::back_inserter(v),
    [](const std::string& file)
    {
      if (file.size() >= 3)
      {
        if (file.substr(0,3) == "ui_") return false;
      }
      if (file.size() >= 4)
      {
        if (file.substr(0,4) == "qrc_") return false;
        if (file.substr(0,4) == "moc_") return false;
      }
      if (file.size() >= 18)
      {
        if (file.substr(file.size() - 18, 18) ==  "_plugin_import.cpp") return false;
      }
      const std::string ext = ribi::fileio::FileIo().GetExtensionNoDot(file);
      return
           ext == "c"
        || ext == "cpp"
        || ext == "h"
        || ext == "hpp"
        || ext == "pri"
        || ext == "pro"
        || ext == "py"
        || ext == "sh";
    }
  );
  return v;
}


std::vector<std::string> ribi::c2h::SortFiles(std::vector<std::string> files) noexcept
{
  std::sort(files.begin(), files.end(),
    [](const std::string& lhs,const std::string& rhs)
    {
      const std::string lhs_base = ribi::fileio::FileIo().GetFileBasename(lhs);
      const std::string rhs_base = ribi::fileio::FileIo().GetFileBasename(rhs);
      const std::string lhs_ext = ribi::fileio::FileIo().GetExtension(lhs);
      const std::string rhs_ext = ribi::fileio::FileIo().GetExtension(rhs);
      static std::string pro(".pro");
      static std::string pri(".pri");
      static std::string sh(".sh");
      static std::string h(".h");
      static std::string cpp(".cpp");
      static std::string py(".py");
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
