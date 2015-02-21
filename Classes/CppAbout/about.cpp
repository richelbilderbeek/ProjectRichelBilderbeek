//---------------------------------------------------------------------------
/*
About, class for containing information about a program
Copyright (C) 2010-2015 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>
#include <boost/version.hpp>

//#include "trace.h"
#pragma GCC diagnostic pop

ribi::About::About(
    const std::string author,
    const std::string file_title,
    const std::string file_description,
    const std::string programmed_on,
    const std::string years,
    const std::string url,
    const std::string version,
    const std::vector<std::string>& version_history) noexcept
  : m_author{author},
    m_file_title{file_title},
    m_file_description{file_description},
    m_libraries{},
    m_programmed_on{programmed_on},
    m_years{years},
    m_url{url},
    m_version{version},
    m_version_history{version_history}
{
  AddLibrary(
    "About version: "
    + GetAboutVersion());
  AddLibrary(
    "Boost version: "
    + GetBoostVersion());
  AddLibrary(
    "STL version: "
    + GetStlVersion()
    + " (GNU ISO C++ library)");
}

void ribi::About::AddLibrary(const std::string& s) noexcept
{
  m_libraries.push_back(s);
  std::sort(m_libraries.begin(),m_libraries.end());
}

std::vector<std::string> ribi::About::CreateAboutText() const noexcept
{
  const std::vector<std::string> v
  {
    m_file_title + ", version " + m_version,
    "Copyright (C) " + m_years + " " + m_author,
    "Programmed on " + m_programmed_on,
    "by " + m_author,
    "",
    m_file_title + " can be downloaded from " + m_url,
    "Licenced under GPL 3.0"
  };
  return v;
}

std::vector<std::string> ribi::About::CreateLibrariesUsedText() const noexcept
{
  std::vector<std::string> v;
  v.push_back("Libraries and classes used: ");
  for(const std::string& s: m_libraries)
  {
    v.push_back(" * " + s);
  }
  return v;
}

std::vector<std::string> ribi::About::CreateLicenceText() const noexcept
{
  std::vector<std::string> v{
    m_file_title + ", " + m_file_description,
    "Copyright (C) " + m_years + " " + m_author,
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

std::vector<std::string> ribi::About::CreateVersionHistory() const noexcept
{
  std::vector<std::string> v;
  v.push_back("Version history:");
  v.push_back(" * YYYY-MM-DD: version X.Y: [description]");
  for(const std::string& s: m_version_history)
  {
    v.push_back(" * " + s);
  }
  return v;
}

std::string ribi::About::GetAboutVersion() noexcept
{
  return "1.7";
}

std::vector<std::string> ribi::About::GetAboutVersionHistory() noexcept
{
  return {
    "2011-01-07: version 1.0: initial version",
    "2011-01-11: version 1.1: added simple getters",
    "2011-09-12: version 1.2: added operator<<",
    "2012-01-08: version 1.3: fixed grammatical error",
    "2012-01-26: version 1.4: removed BOOST_FOREACH",
    "2013-04-29: version 1.5: added #ifdefs for GCC 4.4.0"
    "2013-09-05: version 1.6: transition to namespace ribi"
    "2013-09-16: version 1.7: noexcept added"
  };
}

std::string ribi::About::GetBoostVersion() noexcept
{
  std::string s = BOOST_LIB_VERSION;
  std::replace(s.begin(),s.end(),'_','.');
  return s;
}

std::string ribi::About::GetStlVersion() noexcept
{
  return boost::lexical_cast<std::string>(__VERSION__);
}

std::ostream& ribi::operator<<(std::ostream& os,const About& a) noexcept
{
  {
    const std::vector<std::string> v{a.CreateAboutText()};
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  }
  os
    << '\n';
  {
    std::vector<std::string> v{a.CreateLibrariesUsedText()};
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  }
  os
    << '\n';
  {
    std::vector<std::string> v{a.CreateVersionHistory()};
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(os,"\n"));
  }
  os
    << '\n'
    << "Licence:\n";
  {
    std::vector<std::string> v{a.CreateLicenceText()};
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
