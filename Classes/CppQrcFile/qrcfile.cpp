//---------------------------------------------------------------------------
/*
QrcFile, class to parse Qt Project files
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
//From http://www.richelbilderbeek.nl/CppQrcFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "qrcfile.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/algorithm/string/trim.hpp>
#include <boost/function.hpp>
#include <boost/xpressive/xpressive.hpp>

#include "fileio.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QrcFile::QrcFile(const std::string& filename)
  : m_files{},
    m_qrc_filename{filename}
{
  #ifndef NDEBUG
  Test();
  if(!ribi::fileio::IsRegularFile(filename)) TRACE(filename);
  assert(ribi::fileio::IsRegularFile(filename)
    && "QrcFile::QrcFile error: .qrc file must exist");
  #endif

  std::ifstream file(filename.c_str());

  while (!file.eof())
  {
    std::string s;
    file >> s;
    if (s.empty()) continue;

    const boost::xpressive::sregex rex = boost::xpressive::sregex::compile("<file>.*</file>");
    boost::xpressive::smatch what;
    if( boost::xpressive::regex_match(s, what, rex ) )
    {
      assert(!s.empty());
      s = boost::algorithm::trim_copy(s);
      assert(s.size() > 13);
      s = s.substr(6,s.size() - 13);
      m_files.insert(s);
    }
  }
}

const ribi::About ribi::QrcFile::GetAbout() noexcept
{
  About a(
    "Richel Bilderbeek",
    "QrcFile",
    "class to parse Qt Resource files",
    "the 19th of August 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/CppQrcFile.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

const std::string ribi::QrcFile::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::QrcFile::GetVersionHistory() noexcept
{
  return {
    "2012-06-13: version 1.0: initial version",
    "2013-08-19: version 1.1: replaced Boost.Regex by Boost.Xpressive"
  };
}

#ifndef NDEBUG
void ribi::QrcFile::Test() noexcept
{
  ///Test exactly once
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    //Create a Qt resource file
    {
      std::ofstream f("tmp.txt");
      f << "<RCC>"
        << "    <qresource prefix=\"/images\">"
        << "        <file>Background.png</file>"
        << "        <file>Groups.png</file>"
        << "        <file>Cycle_100.png</file>"
        << "        <file>Experiment_100.png</file>"
        << "        <file>Period_100_58.png</file>"
        << "        <file>ProjectGtstParticipantDialogChatParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogChooseActionParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogFinishedParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogGroupAssign2Parameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogGroupAssignParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogGroupReAssignParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogLoggedInParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogViewResultsGroupParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogNotLoggedInParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogVotingParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogViewResultsVotingParameters.png</file>"
        << "        <file>ProjectGtstParticipantDialogAssignPayoffParameters.png</file>"
        << "    </qresource>"
        << "</RCC>";
    }
    //Check the project file
    QrcFile p("tmp.txt");
    assert(p.GetFiles().count("Period_100_58.png"));
    assert(p.GetFiles().count("ProjectGtstParticipantDialogAssignPayoffParameters.png"));
    //assert(!p.GetFiles().count("RCC"));
  }
}
#endif

std::ostream& ribi::operator<<(std::ostream& os,const QrcFile& f) noexcept
{
  std::for_each(f.m_files.begin(),f.m_files.end(),
    [&os](const std::string& s)
    {
      os << s << '\n';
    }
  );
  return os;
}
