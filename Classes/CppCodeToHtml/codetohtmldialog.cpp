//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2014 Richel Bilderbeek

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
#include "codetohtmldialog.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string.hpp>

#include "codetohtmlfile.h"
#include "codetohtmlfiletypes.h"
#include "codetohtmldialog.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlfoldertypes.h"
#include "codetohtmlinfo.h"
#include "codetohtmltechinfo.h"
#include "codetohtmlreplacer.h"
#include "codetohtmlversion.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

std::vector<std::string> ribi::c2h::Dialog::SnippetToHtml(
  const std::vector<std::string>& code,
  const SnippetType snippet_type) noexcept
{
  FileType file_type = FileType::txt;
  switch (snippet_type)
  {
    case SnippetType::cpp : file_type = FileType::cpp; break;
    case SnippetType::text: file_type = FileType::txt; break;
    case SnippetType::n_snippets:
      assert("Never use SnippetType::n_snippets");
      throw std::logic_error("Never use SnippetType::n_snippets");
  }
  //Convert to HTML, no <code> nor <br/> added yet
  const std::vector<std::string> v {
    Replacer::ToHtml(code,file_type)
  };

  std::vector<std::string> w;
  w.push_back("<p>&nbsp;</p>");
  w.push_back("<!-- start of code -->");
  w.push_back("<table summary=\"snippet\" border = \"1\"><tr><td><code>");
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const std::string& s)
    {
      return s + "<br/>";
    }
  );

  w.push_back("</code></td></tr></table>");
  w.push_back("<!-- end of the code -->");
  w.push_back("<p>&nbsp;</p>");
  w.push_back("<p>&nbsp;</p>");
  w.push_back("<p>&nbsp;</p>");
  w.push_back("<p>&nbsp;</p>");
  w.push_back("<p>&nbsp;</p>");
  return w;
}

std::string ribi::c2h::Dialog::ExtractPageName(const std::string& s) noexcept
{
  // /home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml
  // /home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml/
  // should become
  // ToolCodeToHtml'

  static const boost::xpressive::sregex r
    = boost::xpressive::sregex::compile("[A-Za-z0-9_\\.]*");

  std::vector<std::string> v;
  boost::xpressive::sregex_iterator i(s.begin(),s.end(),r);
  while (i != boost::xpressive::sregex_iterator())
  {
    v.push_back(i->str());
    ++i;
  }
  //Clean up the vector: remove filenames and empty strings
  while (1)
  {
    if (v.empty()) break;
    const std::string t = boost::algorithm::trim_copy( v[ v.size() - 1] );
    if (t.find('.') != std::string::npos || t.empty())
    {
      v.pop_back();
    }
    else break;
  }

  #ifdef REALLY_TRACE_THIS_20130929_28764723047972338294764627389
  const std::size_t sz = v.size();
  TRACE(sz);
  for (std::size_t i=0; i!=sz; ++i)
  {
    std::stringstream s;
    s << i << '/' << sz << ": '" << v[i] << "'";
    TRACE(s.str());
  }
  #endif
  const std::string t = v.empty() ? std::string() : v[v.size() - 1];


  #ifdef USE_BOOST_XPRESSIVE_78263785634856349
  static const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "(.*)?"          //Optional super folders
      "(/|\\\\)?"      //(back)slash
      "([A-Za-z0-9]*)" //Here is the booty
      "(/|\\\\)?"      //(back)slash
      "(([A-Za-z0-9]*)(\\.)([A-Za-z0-9]*))?" //An optional filename
      "(/|\\\\)?"    //Perhaps possible trailing (back)slash
      "\\>");

  boost::xpressive::smatch what;

  std::string t;
  if( boost::xpressive::regex_match(s, what, rex ) )
  {
    const std::size_t sz = what.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      std::stringstream s;
      s << i << "/" << sz << ": '" << what[i] << "'";
      TRACE(s.str());
    }
    t = what[1];
  }
  #endif //USE_BOOST_XPRESSIVE_78263785634856349

  assert(t.find('/') == std::string::npos
    && "A c2h::Info page must not contain a slash");
  assert(t.find('\\') == std::string::npos
    && "A c2h::Info page must not contain a backslash");

  return t;
}

std::vector<std::string> ribi::c2h::Dialog::FileToHtml(
  const std::string& filename) noexcept
{
  const std::vector<std::string> v {
    ribi::fileio::FileIo().FileToVector(filename)
  };
  const FileType file_type = FileTypes::DeduceFileType(filename);
  return Replacer::ToHtml(v,file_type);
}

std::vector<std::string> ribi::c2h::Dialog::FolderToHtml(
  const std::string& foldername) noexcept
{
  assert(fileio::FileIo().IsFolder(foldername));
  const FolderType folder_type = FolderTypes::DeduceFolderType(foldername);
  switch(folder_type)
  {
    case FolderType::foam:
      return FoamFolderToHtml(foldername);
    case FolderType::pro:
      return ProFolderToHtml(foldername);
    case FolderType::txt:
      return TextFolderToHtml(foldername);
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::c2h::Dialog::FolderToHtml");
}

std::vector<std::string> ribi::c2h::Dialog::FoamFolderToHtml(
  const std::string& foldername) noexcept
{
  assert(fileio::FileIo().IsFolder(foldername));
  assert(foldername.back() != '\\');
  assert(foldername.back() != '/');

  std::vector<std::string> v;
  //Header
  {
    HeaderType header_type = HeaderType::foam;
    const std::vector<std::string> w {
      Header::ToHtml(header_type,foldername)
    };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Info
  {
    const boost::shared_ptr<const Info> info(new Info);
    const std::vector<std::string> w {
      info->ToHtml(ExtractPageName(foldername))
    };

    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Body
  {
    const std::vector<std::string> files_no_path {
      fileio::FileIo().GetFilesInFolderRecursive(foldername)
    };
    std::vector<std::string> files;
    std::transform(
      files_no_path.begin(),
      files_no_path.end(),
      std::back_inserter(files),
      [foldername](const std::string& s)
      {
        //If the path is already complete, return it
        if (ribi::fileio::FileIo().IsRegularFile(s))
        {
          return s;
        }
        //Prepend the folder name
        const std::string t {
          foldername
          + ribi::fileio::FileIo().GetPathSeperator()
          + s
        };
        #ifndef NDEBUG
        if(!ribi::fileio::FileIo().IsRegularFile(t))
        {
          TRACE("ERROR");
          TRACE(foldername); TRACE(s); TRACE(t);
        }
        #endif
        assert(ribi::fileio::FileIo().IsRegularFile(t));
        return t;
      }
    );

    #ifndef NDEBUG
    for (const std::string& file: files)
    {
      if (!ribi::fileio::FileIo().IsRegularFile(file)) { TRACE(file); }
      assert(ribi::fileio::FileIo().IsRegularFile(file));
    }
    #endif

    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        assert(ribi::fileio::FileIo().IsRegularFile(filename));
        const boost::shared_ptr<File> content {
          new File(filename,FileType::txt)
        };
        const std::vector<std::string> w = content->GetHtml();
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    );
  }
  //Footer
  {
    const std::vector<std::string> w { Footer::ToHtml(FooterType::foam) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

std::vector<std::string> ribi::c2h::Dialog::GetProFilesInFolder(
  const std::string& folder)
{
  return ribi::fileio::FileIo().GetFilesInFolderByRegex(folder,".*\\.(pro)\\>");
}


std::vector<std::string> ribi::c2h::Dialog::ProFolderToHtml(
  const std::string& foldername) noexcept
{
  std::vector<std::string> v;
  //Header
  {
    HeaderType header_type = HeaderType::cpp;
    const std::vector<std::string> w {
      Header::ToHtml(header_type,foldername)
    };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Collect files
  {
    const std::vector<std::string> pro_files_no_path {
      GetProFilesInFolder(foldername)
    };
    std::vector<std::string> pro_files;
    std::transform(
      pro_files_no_path.begin(),
      pro_files_no_path.end(),
      std::back_inserter(pro_files),
      [foldername](const std::string& s)
      {
        const std::string t {
          foldername
          + ribi::fileio::FileIo().GetPathSeperator()
          + s
        };
        return t;
      }
    );

    #ifndef NDEBUG
    for (const std::string& pro_file: pro_files)
    {
      if (!ribi::fileio::FileIo().IsRegularFile(pro_file)) { TRACE(pro_file); }
      assert(ribi::fileio::FileIo().IsRegularFile(pro_file));
    }
    #endif
    //Info
    {
      const boost::shared_ptr<const Info> info(new Info);
      const std::vector<std::string> w {
        info->ToHtml(ExtractPageName(foldername))
      };
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }

    //TechInfo
    const boost::shared_ptr<const TechInfo> techInfo(new TechInfo(pro_files));
    const std::vector<std::string> w = techInfo->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    const std::vector<std::string> files_no_path {
      GetSortedFilesInFolder(foldername)
    };
    std::vector<std::string> files;
    std::transform(files_no_path.begin(),files_no_path.end(),std::back_inserter(files),
      [foldername](const std::string& s)
      {
        const std::string t {
          foldername + fileio::FileIo().GetPathSeperator() + s
        };
        if (!ribi::fileio::FileIo().IsRegularFile(t))
        {
          TRACE("ERROR"); TRACE(s); TRACE(foldername); TRACE(t);
        }
        assert(ribi::fileio::FileIo().IsRegularFile(t));
        return t;
      }
    );

    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        assert(ribi::fileio::FileIo().IsRegularFile(filename));
        const boost::shared_ptr<File> content {
          new File(filename)
        };
        const std::vector<std::string> w = content->GetHtml();
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    );
  }
  {
    const std::vector<std::string> w { Footer::ToHtml(FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

std::vector<std::string> ribi::c2h::Dialog::TextFolderToHtml(
  const std::string& foldername ) noexcept
{
  assert(fileio::FileIo().IsFolder(foldername));
  assert(foldername.back() != '\\');
  assert(foldername.back() != '/');

  std::vector<std::string> v;
  //Header
  {
    HeaderType header_type = HeaderType::cpp;
    const std::vector<std::string> w {
      Header::ToHtml(header_type,foldername)
    };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Body
  {
    const std::vector<std::string> files_no_path {
      fileio::FileIo().GetFilesInFolderRecursive(foldername)
    };
    std::vector<std::string> files;
    std::transform(
      files_no_path.begin(),
      files_no_path.end(),
      std::back_inserter(files),
      [foldername](const std::string& s)
      {
        //If the path is already complete, return it
        if (ribi::fileio::FileIo().IsRegularFile(s))
        {
          return s;
        }
        //Prepend the folder name
        const std::string t {
          foldername
          + ribi::fileio::FileIo().GetPathSeperator()
          + s
        };
        #ifndef NDEBUG
        if(!ribi::fileio::FileIo().IsRegularFile(t))
        {
          TRACE("ERROR");
          TRACE(foldername); TRACE(s); TRACE(t);
        }
        #endif
        assert(ribi::fileio::FileIo().IsRegularFile(t));
        return t;
      }
    );

    #ifndef NDEBUG
    for (const std::string& file: files)
    {
      if (!ribi::fileio::FileIo().IsRegularFile(file)) { TRACE(file); }
      assert(ribi::fileio::FileIo().IsRegularFile(file));
    }
    #endif

    std::for_each(files.begin(),files.end(),
      [&v](const std::string& filename)
      {
        assert(ribi::fileio::FileIo().IsRegularFile(filename));
        const boost::shared_ptr<File> content {
          new File(filename,FileType::txt)
        };
        const std::vector<std::string> w = content->GetHtml();
        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    );
  }
  //Footer
  {
    const std::vector<std::string> w { Footer::ToHtml(FooterType::cpp) };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  return v;
}

#ifndef NDEBUG
void ribi::c2h::Dialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  assert(ExtractPageName("X") == "X");
  assert(ExtractPageName("/X") == "X");
  assert(ExtractPageName("/A/X") == "X");
  assert(ExtractPageName("/A/B/X") == "X");
  assert(ExtractPageName("/A/B/C/X") == "X");
  assert(ExtractPageName("/X/") == "X");
  assert(ExtractPageName("/A/X/") == "X");
  assert(ExtractPageName("/A/B/X/") == "X");
  assert(ExtractPageName("/A/B/C/X/") == "X");

  assert(ExtractPageName("\\X") == "X");
  assert(ExtractPageName("\\A\\X") == "X");
  assert(ExtractPageName("\\A\\B\\X") == "X");
  assert(ExtractPageName("\\A\\B\\C\\X") == "X");
  assert(ExtractPageName("\\X\\") == "X");
  assert(ExtractPageName("\\A\\X\\") == "X");
  assert(ExtractPageName("\\A\\B\\X\\") == "X");
  assert(ExtractPageName("\\A\\B\\C\\X\\") == "X");

  assert(ExtractPageName("/X") == "X");
  assert(ExtractPageName("/A\\X") == "X");
  assert(ExtractPageName("/A\\B/X") == "X");
  assert(ExtractPageName("\\A\\B/C/X") == "X");
  assert(ExtractPageName("\\X/") == "X");
  assert(ExtractPageName("/A\\X/") == "X");
  assert(ExtractPageName("/A/B\\X/") == "X");
  assert(ExtractPageName("/A/B\\C/X/") == "X");

  assert(ExtractPageName("main.cpp") == "");
  assert(ExtractPageName("/X/main.cpp") == "X");
  assert(ExtractPageName("/A/X/main.cpp") == "X");
  assert(ExtractPageName("/A/B/X/main.cpp") == "X");
  assert(ExtractPageName("/A/B/C/X/main.cpp") == "X");
  assert(ExtractPageName("/X/main.cpp/") == "X");
  assert(ExtractPageName("/A/X/main.cpp/") == "X");
  assert(ExtractPageName("/A/B/X/main.cpp/") == "X");
  assert(ExtractPageName("/A/B/C/X/main.cpp/") == "X");

  assert(ExtractPageName("/home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml")
    == "ToolCodeToHtml");

  //GetProFiles
  {
    //Always first remove the temp file
    const std::string filename = fileio::FileIo().GetTempFileName() + ".pro";
    if (ribi::fileio::FileIo().IsRegularFile(filename)) { ribi::fileio::FileIo().DeleteFile(filename); }
    assert(!ribi::fileio::FileIo().IsRegularFile(filename));

    const std::size_t n = GetProFilesInFolder("").size();
    {
      std::ofstream f(filename.c_str());
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
    ribi::fileio::FileIo().DeleteFile(filename);
    assert(!ribi::fileio::FileIo().IsRegularFile(filename));
    const std::size_t q = GetProFilesInFolder("").size();
    assert(n == q);
  }
  //Check that .PNG files are
  {
    const boost::shared_ptr<File> content { new File("tmp.png") };
    const std::vector<std::string> w = content->GetHtml();
    assert(w.size() == 8);
    assert(w[0].substr(0,4) == "<h2>");
    assert(w[1] == "<p>&nbsp;</p>");
    assert(w[2].substr(0,11) == "<p><img src");
    assert(w[3] == "<p>&nbsp;</p>");
    assert(1==2);
  }
  //DeduceFolderType

  //Check if Info is added

  //Check if CodeToHtml creates a clean HTML file when it converts itself
  #ifndef _WIN32
  assert(IsTidyInstalled() && "While I know I have tidy installed");
  if (IsTidyInstalled())
  {
    const std::string filename = "../ToolCodeToHtml/qtmain.cpp";
    if (ribi::fileio::FileIo().IsRegularFile(filename))
    {
      const std::vector<std::string> v { Dialog::FileToHtml(filename) };
      assert(IsCleanHtml(v) && "Assume tidy HTML");
    }
    else
    {
      TRACE("Warning: ToolCodeToHtml has not tested itself on its own code upon construction");
    }
  }
  else
  {
    TRACE("WARNING: 'tidy' not found, check if CodeToHtml generates clean HTML code is skipped");
  }
  if (IsTidyInstalled())
  {
    const std::string path = "../ToolCodeToHtml";
    if (ribi::fileio::FileIo().IsFolder(path))
    {
      const std::vector<std::string> v { Dialog::FolderToHtml(path) };
      assert(IsCleanHtml(v) && "Assume tidy HTML");
    }
    else
    {
      TRACE("Warning: ToolCodeToHtml has not tested itself on its own code upon construction");
    }
  }
  else
  {
    TRACE("WARNING: 'tidy' not found, check if CodeToHtml generates clean HTML code is skipped");
  }
  #endif
}
#endif
