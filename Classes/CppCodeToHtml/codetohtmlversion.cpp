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
#include "codetohtmlversion.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>


#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/version.hpp>

#include <QFile>

#ifndef _WIN32
#include <Wt/WConfig.h>
#endif

#include "codetohtml.h"
#pragma GCC diagnostic pop

const std::string Version::GetBoostVersion()
{
  std::string s = BOOST_LIB_VERSION;
  std::replace(s.begin(),s.end(),'_','.');
  return s;
}

const std::string Version::GetGccVersion()
{
  return
      boost::lexical_cast<std::string>(__GNUC__)
    + std::string(".")
    + boost::lexical_cast<std::string>(__GNUC_MINOR__)
    + std::string(".")
    + boost::lexical_cast<std::string>(__GNUC_PATCHLEVEL__);
}

#ifndef _WIN32
const std::string Version::GetLubuntuVersion()
{
  const std::string filename = std::tmpnam(0);
  //Save info to temporary filename
  {
    const std::string cmd
      = std::string("cat /etc/*-release > ")
      + filename;
    const int error_code = std::system(cmd.c_str());
    if (error_code) return "unknown";
  }
  //Read info to std::vector
  std::vector<std::string> v;
  {
    std::ifstream f(filename.c_str());
    std::string s;
    for (int i=0; !f.eof(); ++i)
    {
      std::getline(f,s);
      v.push_back(s);
    }
  }
  //Analyze std::vector
  BOOST_FOREACH(const std::string& s,v)
  {
    if (s.size() > 15
      && s.substr(0,15)=="DISTRIB_RELEASE")
    {
      const int i = s.find_last_of("=");
      std::remove(filename.c_str());
      return s.substr(i+1,s.size()-(i+1));
    }
  }
  return "unknown";
}
#endif

#ifndef _WIN32
const std::string Version::GetLubuntuVersionCodename()
{
  const std::string filename = std::tmpnam(0);
  //Save info to temporary filename
  {
    const std::string cmd
      = std::string("cat /etc/*-release > ")
      + filename;
    const int error_code = std::system(cmd.c_str());
    if (error_code) return "unknown";
  }
  //Read info to std::vector
  std::vector<std::string> v;
  {
    std::ifstream f(filename.c_str());
    std::string s;
    for (int i=0; !f.eof(); ++i)
    {
      std::getline(f,s);
      v.push_back(s);
    }
  }
  //Analyze std::vector
  BOOST_FOREACH(const std::string& s,v)
  {
    if (s.size() > 16
      && s.substr(0,16)=="DISTRIB_CODENAME")
    {
      const int i = s.find_last_of("=");
      std::remove(filename.c_str());
      return s.substr(i+1,s.size()-(i+1));
    }
  }
  return "unknown";
}
#endif

const std::string Version::GetQtVersion()
{
  return QT_VERSION_STR;
}

#ifndef _WIN32
const std::string Version::GetQtCreatorVersion()
{
  //'2>' denotes -AFAIK- 'Write to file only, no screen output'
  const int error = std::system("qtcreator -version 2> tmp.txt");
  if (error)
  {
    return "unknown";
  }
  assert(error == 0);
  const std::vector<std::string> v = FileToVector("tmp.txt");

  //Delete file
  std::remove("tmp.txt");

  const std::size_t sz = v.size();
  assert(sz > 1);
  for (std::size_t i=0; i!=sz; ++i)
  {
    const std::string& s = v[i];
    if (s.substr(0,11) == std::string("Qt Creator "))
    {
      return s.substr(11,5);
    }
  }
  return "unknown";
}
#endif

const std::string Version::GetStlVersion()
{
  return __VERSION__;
}

#ifndef _WIN32
const std::string Version::GetUbuntuVersion()
{
  const std::string filename = std::tmpnam(0);
  //Save info to temporary filename
  {
    const std::string cmd
      = std::string("cat /etc/*-release > ")
      + filename;
    const int error_code = std::system(cmd.c_str());
    if (error_code) return "unknown";
  }
  //Read info to std::vector
  std::vector<std::string> v;
  {
    std::ifstream f(filename.c_str());
    std::string s;
    for (int i=0; !f.eof(); ++i)
    {
      std::getline(f,s);
      v.push_back(s);
    }
  }
  //Analyze std::vector
  BOOST_FOREACH(const std::string& s,v)
  {
    if (s.size() > 15
      && s.substr(0,15)=="DISTRIB_RELEASE")
    {
      const int i = s.find_last_of("=");
      std::remove(filename.c_str());
      return s.substr(i+1,s.size()-(i+1));
    }
  }
  return "unknown";
}
#endif

#ifndef _WIN32
const std::string Version::GetUbuntuVersionCodename()
{
  const std::string filename = std::tmpnam(0);
  //Save info to temporary filename
  {
    const std::string cmd = "cat /etc/*-release > " + filename;
    const int error_code = std::system(cmd.c_str());
    if (error_code) return "unknown";
  }
  //Read info to std::vector
  std::vector<std::string> v;
  {
    std::ifstream f(filename.c_str());
    std::string s;
    for (int i=0; !f.eof(); ++i)
    {
      std::getline(f,s);
      v.push_back(s);
    }
  }
  //Analyze std::vector
  BOOST_FOREACH(const std::string& s,v)
  {
    if (s.size() > 16
      && s.substr(0,16)=="DISTRIB_CODENAME")
    {
      const int i = s.find_last_of("=");
      std::remove(filename.c_str());
      return s.substr(i+1,s.size()-(i+1));
    }
  }
  return "unknown";
}
#endif

const std::string Version::GetVirtualBoxVersion()
{
  const std::string filename = std::tmpnam(0);
  //Save info to temporary file
  {
    const std::string cmd
      = std::string("vboxmanage --version > ")
      + filename;
    const int error_code = std::system(cmd.c_str());
    if (error_code) return "unknown";
  }
  {
    std::ifstream f(filename.c_str());
    std::string version;
    f >> version;
    //Delete temporary file
    std::remove(filename.c_str());
    return version;
  }
  return "unknown";
}

const std::string Version::GetWineVersion()
{
  const std::string filename = std::tmpnam(0);
  //Save info to temporary file
  {
    const std::string cmd
      = std::string("wine --version > ")
      + filename;
    const int error_code = std::system(cmd.c_str());
    if (error_code) return "unknown";
  }
  {
    std::ifstream f(filename.c_str());
    std::string version;
    //Reads wine-x.y.z
    f >> version;
    //Remove 'wine-' prefix
    version = version.substr(5,version.size() - 5);
    //Delete temporary file
    std::remove(filename.c_str());
    return version;
  }
  return "unknown";
}

const std::string Version::GetWtVersion()
{
  #ifndef _WIN32
  return WT_VERSION_STR;
  #else
  return "?.?.?";
  #endif
}
