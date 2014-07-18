//---------------------------------------------------------------------------
/*
QtCreatorProFile, class to parse Qt Project files
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
//From http://www.richelbilderbeek.nl/CppQtCreatorProFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtcreatorprofile.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/function.hpp>

#include "fileio.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtCreatorProFile::QtCreatorProFile(const std::string& filename)
  :
    m_config{},
    m_defines{},
    m_forms{},
    m_headers{},
    m_includepath{},
    m_libs{},
    m_other_files{},
    m_pri_files{},
    m_pro_filename{fileio::FileIo().ConvertPathToUnix(filename)},
    m_qmake_cxxflags{},
    m_qt{},
    m_resources{},
    m_target{},
    m_template{},
    m_sources{}
{
  #ifndef NDEBUG
  Test();
  assert(ribi::fileio::FileIo().IsRegularFile(m_pro_filename));
  assert(fileio::FileIo().IsUnixPath(m_pro_filename));
  #endif

  std::vector<std::string> v{ribi::fileio::FileIo().FileToVector(m_pro_filename)};
  RemoveComments(v);
  DoReplacements(v);
  std::stringstream data;
  std::copy(std::begin(v),std::end(v),std::ostream_iterator<std::string>(data," "));
  Parse(data);
}

void ribi::QtCreatorProFile::DoReplacements(std::vector<std::string>& v)
{
  for (std::string& s: v)
  {
    boost::algorithm::replace_all(s,"include (","include(");
  }
}

ribi::About ribi::QtCreatorProFile::GetAbout() noexcept
{
  ribi::About a(
    "Richel Bilderbeek",
    "QtCreatorProFile",
    "class to parse Qt Project files",
    "the 19th of August 2013",
    "2010-2014",
    "http://www.richelbilderbeek.nl/CppQtCreatorProFile.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

std::string ribi::QtCreatorProFile::GetVersion() noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::QtCreatorProFile::GetVersionHistory() noexcept
{
  return {
    "2010-12-19: version 1.0: initial version",
    "2011-01-06: version 1.1: added GetCommonRoot and GetLibs member functions, added operator<<",
    "2011-09-11: version 1.2: fixed bug",
    "2012-02-25: version 1.3: added GetAbout member function",
    "2012-02-28: version 1.4: added support for INCLUDEPATH, FORMS, OTHER_FILES, RESOURCES and QMAKE_CXXFLAGS",
    "2012-05-30: version 1.5: added SimplifyPath",
    "2012-08-13: version 1.6: modifiers like win32 and unix are ignored, instead of yielding an error",
    "2012-12-23: version 1.7: set destructor to private, except for boost::checked_delete",
    "2012-12-23: version 1.8: renamed to QtCreatorProFile due to naming conflicts when cross-compiling",
    "2013-05-18: version 2.0: simplified architecture by removing file I/O",
    "2013-08-19: version 2.1: replaced Boost.Regex by Boost.Xpressive, removed Boost.Filesystem",
    "2014-01-27: version 2.2: removes all comments, can detect includes of .pri files",
    "2014-05-02: version 3.0: use UNIX path seperators only"
  };
}

void ribi::QtCreatorProFile::Parse(std::stringstream& data)
{
  const bool verbose{false};
  std::set<std::string> * p = nullptr; //A set to write to
  enum class Prefix { none, plus, minus };
  Prefix prefix = Prefix::none;
  while (data)
  {
    std::string s;
    data >> s;
    if (verbose) { TRACE(s); }
    assert(s[0] != '#' && "Comments are already removed");
    if (s[0] == '{') continue;
    if (s[0] == '}') continue;
    if (s[0] == '\\') continue;
    if (s.size() > 7 && s.substr(0,7) == "include")
    {
      std::string t = s.substr(8,s.size() - 8 - 1);
      if (verbose) { TRACE(t); }
      while (t[0] == ' ' || t[0] == '(') t = t.substr(1,t.size()-1);
      if (verbose) { TRACE(t); }
      while (t.back() == ' ' || t.back() == ')') t.pop_back();
      if (verbose) { TRACE(t); }
      assert(t.find('(') == std::string::npos);
      assert(t.find(')') == std::string::npos);
      m_pri_files.insert(t);
      continue;
    }
    const std::vector<std::string> conditional_sections {
      "unix", "win32", "static", "debug", "release"
    };
    if (std::count(conditional_sections.begin(),conditional_sections.end(),s))
    {
      p = nullptr;
      continue;
    }
    const std::map<std::string,std::set<std::string>* > m {
      { "CONFIG"        ,&m_config },
      { "DEFINES"       ,&m_defines },
      { "FORMS"         ,&m_forms },
      { "HEADERS"       ,&m_headers },
      { "INCLUDEPATH"   ,&m_includepath },
      { "LIBS"          ,&m_libs },
      { "OTHER_FILES"   ,&m_other_files },
      { "QMAKE_CXXFLAGS",&m_qmake_cxxflags },
      { "QT"            ,&m_qt },
      { "RESOURCES"     ,&m_resources },
      { "SOURCES"       ,&m_sources },
      { "TARGET"        ,&m_target },
      { "TEMPLATE"      ,&m_template }
    };
    const std::map<std::string,std::set<std::string>* >::const_iterator iter {
      std::find_if(std::begin(m),std::end(m),
        [s](const std::pair<std::string,std::set<std::string>* > sub_pair)
        {
          return sub_pair.first == s;
        }
      )
    };
    if (iter != std::end(m))
    {
      if (verbose) { const std::string msg = "Set pointer to " + iter->first; TRACE(msg); }
      p = iter->second;
      prefix = Prefix::none;
      continue;
    }
    //Determine prefixes
    bool has_prefixes = true;
    while (has_prefixes)
    {
      has_prefixes = false;
      if (!s.empty() && s[0] == '+')
      {
        prefix = Prefix::plus;
        s = s.substr(1,s.size() - 1);
        has_prefixes = true;
      }
      else if (!s.empty() && s[0] == '-')
      {
        prefix = Prefix::minus;
        s = s.substr(1,s.size() - 1);
        has_prefixes = true;
      }
      else if (!s.empty() && s[0] == '\\')
      {
        s = s.substr(1,s.size() - 1);
        has_prefixes = true;
      }
      else if (!s.empty() && s[0] == '=')
      {
        s = s.substr(1,s.size() - 1);
        has_prefixes = true;
      }
    }
    //Remove possible postfix
    if (!s.empty())
    {
      if (s[ s.size() - 1] == '\\') s.resize(s.size() - 1);

    }
    if (p && !s.empty())
    {
      if (verbose) { const std::string msg = "Added " + s; TRACE(msg); }
      p->insert(
        (prefix == Prefix::minus ? "-" : "") + s);
    }
  }
}

void ribi::QtCreatorProFile::RemoveComments(std::vector<std::string>& v)
{
  for (std::string& s: v)
  {
    const std::string t = boost::algorithm::trim_copy(s);
    if (t[0] == '#')
    {
      s = "";
      continue;
    }
    if (t.size() >= 7 && t.substr(0,7) == "message")
    {
      s = "";
      continue;
    }

    const auto iter = std::find(std::begin(t),std::end(t),'#');
    if (iter != std::end(t))
    {
      s.assign(std::begin(t),iter);
    }

    assert(std::find(std::begin(s),std::end(s),'#') == std::end(s)
      && "Every comment is removed");
  }

}

#ifndef NDEBUG
void ribi::QtCreatorProFile::Test() noexcept
{
  //Test exactly once
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtCreatorProFile::Test");
  {
    const std::string mypath { fileio::FileIo().GetTempFileName() };
    {
      std::ofstream f(mypath);
      f << "SOURCES += qtmain.cpp";
    }
    //Check the project file
    const QtCreatorProFile p(mypath);
    assert(p.GetSources().size() == 1);
    assert(p.GetSources().count("qtmain.cpp"));
    fileio::FileIo().DeleteFile(mypath.c_str());
  }
  {
    const std::string mypath { fileio::FileIo().GetTempFileName() };
    {
      std::ofstream f(mypath);
      f << "include(something.pri)";
    }
    //Check the project file
    const QtCreatorProFile p(mypath);
    assert(p.GetPriFiles().size() == 1);
    TRACE(*p.GetPriFiles().begin());
    assert(p.GetPriFiles().count("something.pri"));
    fileio::FileIo().DeleteFile(mypath.c_str());
  }
  {
    const std::string mypath { fileio::FileIo().GetTempFileName() };
    {
      std::ofstream f(mypath);
      f << "include (something.pri)";
    }
    //Check the project file
    const QtCreatorProFile p(mypath);
    assert(p.GetPriFiles().size() == 1);
    TRACE(*p.GetPriFiles().begin());
    assert(p.GetPriFiles().count("something.pri"));
    fileio::FileIo().DeleteFile(mypath.c_str());
  }
  {
    const std::string mypath { fileio::FileIo().GetTempFileName() };
    {
      std::ofstream f(mypath);
      f << "HEADERS += header.h #Must remove this comment";
    }
    //Check the project file
    const QtCreatorProFile p(mypath);
    assert(p.GetHeaders().size() == 1);
    assert(p.GetHeaders().count("header.h"));
    fileio::FileIo().DeleteFile(mypath.c_str());
  }
  {
    const std::string mypath { fileio::FileIo().GetTempFileName() };
    {
      std::ofstream f(mypath);
      f << "#-------------------------------------------------\n"
        << "#\n"
        << "# Project created by QtCreator 2010-12-19T16:24:53\n"
        << "#\n"
        << "#-------------------------------------------------\n"
        << "QT       += core\n"
        << "QT       -= gui\n"
        << "LIBS     += -lwt -lboost_regex\n"
        << "TARGET = ToolTestQtCreatorProFile\n"
        << "CONFIG   += console\n"
        << "CONFIG   -= app_bundle\n"
        << "TEMPLATE = app\n"
        << "SOURCES += main.cpp \\\n"
        << "    profile.cpp\n"
        << "HEADERS += \\\n"
        << "    profile.h";
    }
    //Check the project file
    const QtCreatorProFile p(mypath);
    TRACE(p.GetConfig().size());
    assert(p.GetConfig().size() == 2);
    assert(p.GetConfig().count("console"));
    assert(p.GetConfig().count("-app_bundle"));
    assert(p.GetHeaders().size() == 1);
    assert(p.GetHeaders().count("profile.h"));
    assert(p.GetLibs().size() == 2);
    assert(p.GetLibs().count("-lwt"));
    assert(p.GetLibs().count("-lboost_regex"));
    assert(p.GetQtCreatorProFilename() == mypath);
    assert(p.GetQt().size() == 2);
    assert(p.GetQt().count("core"));
    assert(p.GetQt().count("-gui"));
    assert(p.GetSources().size() == 2);
    assert(p.GetSources().count("main.cpp"));
    assert(p.GetSources().count("profile.cpp"));
    assert(p.GetTarget().count("ToolTestQtCreatorProFile") == 1);
    assert(p.GetTemplate().size() == 1);
    assert(p.GetTemplate().count("app"));
    {
      std::stringstream ss;
      ss << p << '\n';
    }
    //TRACE("Test QtCreatorProFile::operator==");
    {
      QtCreatorProFile q(mypath);
      assert(p == q);
    }
    fileio::FileIo().DeleteFile(mypath.c_str());
  }
  //TRACE("Test QtCreatorProFile::Merge");
  {
    const std::string mypath1 { fileio::FileIo().GetTempFileName() };
    const std::string mypath2 { fileio::FileIo().GetTempFileName() };
    {
      std::ofstream f(mypath1);
      f << "#-------------------------------------------------\n"
        << "#\n"
        << "# Project created by QtCreator 2010-12-19T16:24:53\n"
        << "#\n"
        << "#-------------------------------------------------\n"
        << "QT       += core\n"
        << "QT       -= gui\n"
        << "LIBS     += -lwt -lboost_regex\n"
        << "TARGET = ToolTestQtCreatorProFileWebsite\n"
        << "CONFIG   += console\n"
        << "CONFIG   -= app_bundle\n"
        << "TEMPLATE = app\n"
        << "SOURCES += wtmain.cpp \\\n"
        << "    profile.cpp\n"
        << "HEADERS += \\\n"
        << "    profile.h";
    }
    {
      std::ofstream f(mypath2);
      f << "#-------------------------------------------------\n"
        << "#\n"
        << "# Project created by QtCreator 2010-12-19T16:24:53\n"
        << "#\n"
        << "#-------------------------------------------------\n"
        << "QT       -= core\n"
        << "QT       -= gui\n"
        << "LIBS     += -lboost_regex\n"
        << "TARGET = ToolTestQtCreatorProFileConsole\n"
        << "CONFIG   += console\n"
        << "CONFIG   -= app_bundle\n"
        << "TEMPLATE = app\n"
        << "SOURCES += main.cpp \\\n"
        << "    profile.cpp\n"
        << "HEADERS += \\\n"
        << "    profile.h";
    }
    //Check the project file
    const boost::shared_ptr<const QtCreatorProFile> p1(new QtCreatorProFile(mypath1));
    const boost::shared_ptr<const QtCreatorProFile> p2(new QtCreatorProFile(mypath2));
    fileio::FileIo().DeleteFile(mypath1.c_str());
    fileio::FileIo().DeleteFile(mypath2.c_str());
  }
  //Test conditionals
  {
    //Create a project file
    const std::string mypath { fileio::FileIo().GetTempFileName() };
    {
      std::ofstream f(mypath);
      f
        << "QT       += core\n"
        << "unix {\n"
        << "SOURCES += \\\n"
        << "    unix_main.cpp \\\n"
        << "}\n"
        << "win32 {\n"
        << "TARGET = TestTarget\n"
        << "SOURCES += win_main.cpp\n"
        << "}\n"
        << "SOURCES += profile.cpp\n"
        << "HEADERS += \\\n"
        << "    profile.h";
    }
    //Check the project file
    const QtCreatorProFile p(mypath);
    assert(p.GetQt().size() == 1);
    assert(p.GetQt().count("core"));
    assert(p.GetSources().size() == 3);
    assert(p.GetSources().count("unix_main.cpp"));
    assert(p.GetSources().count("win_main.cpp"));
    assert(p.GetSources().count("profile.cpp"));
    assert(p.GetHeaders().size() == 1);
    assert(p.GetHeaders().count("profile.h"));

    //Test operator<<
    {
      std::stringstream ss;
      ss << p << '\n';
    }
    //Test operator==
    {
      QtCreatorProFile q(mypath);
      assert(p == q);
    }
    fileio::FileIo().DeleteFile(mypath.c_str());
  }
  TRACE("Finished QtCreatorProFile::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const QtCreatorProFile& p)
{
  os << "\n";
  for (const std::string pri: p.GetPriFiles())
  {
    os << "include(" << pri << ")" << '\n';
  }
  {
    const std::vector<
      std::pair<
        std::string, boost::function<const std::set<std::string>& (const QtCreatorProFile&)>
        >
      > v = {
        { "CONFIG", &QtCreatorProFile::GetConfig },
        { "DEFINES", &QtCreatorProFile::GetDefines },
        { "FORMS", &QtCreatorProFile::GetForms },
        { "HEADERS", &QtCreatorProFile::GetHeaders },
        { "INCLUDEPATH", &QtCreatorProFile::GetIncludepath },
        { "LIBS", &QtCreatorProFile::GetLibs },
        { "OTHER_FILES", &QtCreatorProFile::GetOtherFiles },
        { "QMAKE_CXXFLAGS", &QtCreatorProFile::GetQmakeCxxflags },
        { "QT", &QtCreatorProFile::GetQt},
        { "RESOURCES", &QtCreatorProFile::GetResources },
        { "SOURCES", &QtCreatorProFile::GetSources },
        { "TARGET", &QtCreatorProFile::GetTarget },
        { "TEMPLATE", &QtCreatorProFile::GetTemplate }
      };

    std::for_each(v.begin(),v.end(),
      [&os,&p](const std::pair<std::string, boost::function<const std::set<std::string>& (const QtCreatorProFile&)> >& pair)
      {
        const std::set<std::string>& w = pair.second(p);
        if (!w.empty())
        {
          os << pair.first << " += \\\n";
          if (w.size() > 1)
          {
            std::transform(w.begin(),--w.end(),std::ostream_iterator<std::string>(os," \\\n"),
              [](const std::string& s) { return "    " + s; } );
          }
          os << "    " + (*(--w.end())) + '\n';
          os << "\n";
        }
      }
    );
  }
  os << "\n";
  os << "#--------------------------------------------------------------------------\n";
  os << "# This file was created by:\n";
  os << "#\n";
  {
    const std::vector<std::string> v = p.GetAbout().CreateAboutText();
    std::transform(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"),
      [](const std::string& s) { return "# " + s; } );
  }
  os << "#\n";
  os << "#\n";
  os << "#\n";
  {
    const std::vector<std::string> v = p.GetAbout().CreateLicenceText();
    std::transform(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"),
      [](const std::string& s) { return "# " + s; } );
  }
  os << "#--------------------------------------------------------------------------";
  return os;
}

bool ribi::operator==(const QtCreatorProFile& lhs, const QtCreatorProFile& rhs)
{
  return
       lhs.m_config == rhs.m_config
    && lhs.m_defines == rhs.m_defines
    && lhs.m_forms == rhs.m_forms
    && lhs.m_headers == rhs.m_headers
    && lhs.m_includepath == rhs.m_includepath
    && lhs.m_libs == rhs.m_libs
    && lhs.m_other_files == rhs.m_other_files
    && lhs.m_pro_filename == rhs.m_pro_filename
    && lhs.m_qmake_cxxflags == rhs.m_qmake_cxxflags
    && lhs.m_qt == rhs.m_qt
    && lhs.m_resources == rhs.m_resources
    && lhs.m_target == rhs.m_target
    && lhs.m_template == rhs.m_template
    && lhs.m_sources == rhs.m_sources;
}
