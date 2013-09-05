//---------------------------------------------------------------------------
/*
About, class for containing information about a program
Copyright (C) 2010 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAbout.htm
//---------------------------------------------------------------------------
#include "about.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"


#if !(__GNUC__ > 4 && __GNUC_MINOR__ > 4)
#include <boost/foreach.hpp>
#endif

#include <boost/lexical_cast.hpp>
#include <boost/version.hpp>
#pragma GCC diagnostic pop


//#include "trace.h"

ribi::About::About(
    const std::string author,
    const std::string file_title,
    const std::string file_description,
    const std::string programmed_on,
    const std::string years,
    const std::string url,
    const std::string version,
    const std::vector<std::string>& version_history)
  : m_author { author },
    m_file_title(file_title),
    m_file_description(file_description),
    m_libraries( {} ),
    m_programmed_on(programmed_on),
    m_years(years),
    m_url(url),
    m_version(version),
    m_version_history(version_history)
{
  AddLibrary(
    std::string("About version: ")
    + GetAboutVersion());
  AddLibrary(
    std::string("Boost version: ")
    + GetBoostVersion());
  AddLibrary(
    std::string("STL version: ")
    + GetStlVersion()
    + std::string(" (GNU ISO C++ library)"));
}

void ribi::About::AddLibrary(const std::string& s)
{
  m_libraries.push_back(s);
  std::sort(m_libraries.begin(),m_libraries.end());
}

const std::vector<std::string> ribi::About::CreateAboutText() const
{
  const std::vector<std::string> v
  {
    m_file_title + std::string(", version ") + m_version,
    std::string("Copyright (C) ") + m_years + std::string(" ") + m_author,
    std::string("Programmed on ") + m_programmed_on,
    std::string("by ") + m_author,
    "",
    m_file_title + std::string(" can be downloaded from ") + m_url,
    "Licenced under GPL 3.0"
  };
  return v;
}

const std::vector<std::string> ribi::About::CreateLibrariesUsedText() const
{
  std::vector<std::string> v;
  v.push_back("Libraries and classes used: ");
  #if __GNUC__ > 4 && __GNUC_MINOR__ > 4
  std::for_each(m_libraries.begin(), m_libraries.end(),
    [&v](const std::string& s)
    {
      assert(!s.empty());
      v.push_back(std::string(" * ") + s);
    }
  );
  #else
  BOOST_FOREACH(const std::string& s, m_libraries)
  {
    v.push_back(std::string(" * ") + s);
  }
  #endif
  return v;
}

const std::vector<std::string> ribi::About::CreateLicenceText() const
{
  std::vector<std::string> v {
    m_file_title + std::string(", ") + m_file_description,
    std::string("Copyright (C) ") + m_years + std::string(" ") + m_author,
    "",
    "This program is free software: you can redistribute it and/or modify",
    "it under the terms of the GNU General Public License as published by",
    "the Free Software Foundation, either version 3 of the License, or",
    "(at your option) any later version.",
    "",
    "This program is distributed in the hope that it will be useful,",
    "but WITHOUT ANY WARRANTY; without even the implied warranty of",
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the",
    "GNU General Public License for more details.",
    "You should have received a copy of the GNU General Public License",
    "along with this program. If not, see <http://www.gnu.org/licenses/>."
  };
  return v;
}

const std::vector<std::string> ribi::About::CreateVersionHistory() const
{
  std::vector<std::string> v;
  v.push_back("Version history:");
  v.push_back(" * YYYY-MM-DD: version X.Y: [description]");
  #if __GNUC__ > 4 && __GNUC_MINOR__ > 4
  std::for_each(m_version_history.begin(), m_version_history.end(),
    [&v](const std::string& s)
    {
      v.push_back(std::string(" * ") + s);
    }
  );
  #else
  BOOST_FOREACH(const std::string& s, m_version_history)
  {
    v.push_back(std::string(" * ") + s);
  }
  #endif
  return v;
}

const std::string ribi::About::GetAboutVersion()
{
  return "1.5";
}

const std::vector<std::string> ribi::About::GetAboutVersionHistory()
{
  const std::vector<std::string> v {
    "2011-01-07: version 1.0: initial version",
    "2011-01-11: version 1.1: added simple getters",
    "2011-09-12: version 1.2: added operator<<",
    "2012-01-08: version 1.3: fixed grammatical error",
    "2012-01-26: version 1.4: removed BOOST_FOREACH",
    "2013-04-29: version 1.5: added #ifdefs for GCC 4.4.0"
    "2013-09-05: version 1.6: transition to namespace ribi"
  };
  return v;
}

const std::string ribi::About::GetBoostVersion()
{
  std::string s = BOOST_LIB_VERSION;
  std::replace(s.begin(),s.end(),'_','.');
  return s;
}

const std::string ribi::About::GetStlVersion()
{
  return boost::lexical_cast<std::string>(__VERSION__);
}

std::ostream& ribi::operator<<(std::ostream& os,const About& a)
{
  {
    const std::vector<std::string> v = a.CreateAboutText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  }
  os
    << '\n';
  {
    std::vector<std::string> v = a.CreateLibrariesUsedText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  }
  os
    << '\n';
  {
    std::vector<std::string> v = a.CreateVersionHistory();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  }
  os
    << '\n'
    << "Licence:\n";
  {
    std::vector<std::string> v = a.CreateLicenceText();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  }
  os
    << '\n'
    << "Source code built on "
    << __DATE__
    << " "
    << __TIME__
    << '\n'
  #ifdef NDEBUG
    << "Release version"
  #else
    << "Debug version"
  #endif
    << '\n';
  return os;
}
