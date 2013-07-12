//---------------------------------------------------------------------------
/*
QrcFile, class to parse Qt Project files
Copyright (C) 2010-2012 Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qrcfile.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <boost/regex.hpp>
#pragma GCC diagnostic pop

#include "trace.h"

QrcFile::QrcFile(const std::string& filename)
  : m_qrc_filename(filename)
{
  #ifndef NDEBUG
  Test();
  if(!boost::filesystem::is_regular_file(filename)) TRACE(filename);
  assert(boost::filesystem::is_regular_file(filename)
    && "QrcFile::QrcFile error: .qrc file must exist");
  #endif

  std::ifstream file(filename.c_str());

  while (!file.eof())
  {
    std::string s;
    file >> s;
    if (s.empty()) continue;
    if (boost::regex_search(s,boost::regex("<file>.*</file>")))
    {
      assert(!s.empty());
      s = boost::algorithm::trim_copy(s);
      assert(s.size() > 13);
      s = s.substr(6,s.size() - 13);
      m_files.insert(s);
    }
  }
}

const std::vector<std::string> QrcFile::FileToVector(const std::string& filename)
{
  assert(boost::filesystem::is_regular_file(filename));
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

const About QrcFile::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "QrcFile",
    "class to parse Qt Resource files",
    "the 13th of June 2012",
    "2012",
    "http://www.richelbilderbeek.nl/CppQrcFile.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}

const std::string QrcFile::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QrcFile::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-06-13: version 1.0: initial version");
  return v;
}

void QrcFile::Test()
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

std::ostream& operator<<(std::ostream& os,const QrcFile& f)
{
  std::for_each(f.m_files.begin(),f.m_files.end(),
    [&os](const std::string& s)
    {
      os << s << '\n';
    }
  );
  return os;
}

