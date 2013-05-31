//---------------------------------------------------------------------------
/*
ndsmake, tool to generate NDS makefile from Qt Creator project file
Copyright (C) 2010 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolNdsmake.htm
//---------------------------------------------------------------------------
#include "ndsmake.h"
//---------------------------------------------------------------------------
Ndsmake::Ndsmake(const std::string filename)
  : m_proFile(filename)
{
  m_command = CreateCommand();
}
//---------------------------------------------------------------------------
const std::string Ndsmake::CreateCommand() const
{
  //Copy ProFile files to the needed folders
  std::string s
    = "cd .. ;"
    + std::string("mkdir ") + m_proFile.GetBuildDir() + "; "
    + "cd " + m_proFile.GetBuildDir() + "; "
    + "mkdir source; ";
  //Start copying all files
  {
    const std::size_t sz = m_proFile.GetHeaders().size();
    for (std::size_t i = 0; i!=sz; ++i)
    //BOOST_FOREACH(const std::string& f,m_proFile.GetHeaders())
    {
      const std::string f = m_proFile.GetHeaders()[i];
      s += std::string("cp ")
        + m_proFile.GetCurDirFull()
        + std::string("/")
        + f
        + std::string(" ")
        + m_proFile.GetBuildDirFull()
        + std::string("/source/")
        + f
        + std::string("; ");
    }
  }
  {
    const std::size_t sz = m_proFile.GetSources().size();
    for (std::size_t i = 0; i!=sz; ++i)
    //BOOST_FOREACH(const std::string& f,m_proFile.GetSources())
    {
      const std::string f = m_proFile.GetSources()[i];
      s += std::string("cp ")
        + m_proFile.GetCurDirFull()
        + std::string("/")
        + f
        + std::string(" ")
        + m_proFile.GetBuildDirFull()
        + std::string("/source/")
        + f
        + std::string("; ");
    }
  }
  return s;
}
//---------------------------------------------------------------------------
const std::vector<std::string> Ndsmake::GetHelp()
{
  std::vector<std::string> v;
  v.push_back("Usage: ndsmake [options] [target]");
  v.push_back("");
  v.push_back("[target] must be the full path and filename of your Qt Creator project");
  v.push_back("for example: 'ndsmake /myqtfolder/myqtproject.pro'");
  v.push_back("");
  v.push_back("Options:");
  v.push_back("  --help: prints this message and exits");
  v.push_back("  --history: prints this ndsmake version history and exits");
  v.push_back("  --licence: prints the ndsmake licence and exits");
  v.push_back("  --version: print the current version of ndsmake and exits");
  return v;
}
//---------------------------------------------------------------------------
const std::vector<std::string> Ndsmake::GetHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2010-10-10: version 0.1: incomplete, could not be run from Qt Creator");
  v.push_back("2010-10-13: version 1.0: initial release, works from Qt Creator, tested by TestNdsmake");
  v.push_back("2010-12-19: version 1.1: added extra commands, use of ProFile class");
  v.push_back("2010-12-19: version 1.2: use of Ndsmake class");
  return v;
}
//---------------------------------------------------------------------------
const std::vector<std::string> Ndsmake::GetLicence()
{
  std::vector<std::string> v;
  v.push_back("ndsmake, tool to generate NDS makefile from Qt Creator project file");
  v.push_back("Copyright (C) 2010 Richel Bilderbeek");
  v.push_back("");
  v.push_back("This program is free software: you can redistribute it and/or modify");
  v.push_back("it under the terms of the GNU General Public License as published by");
  v.push_back("the Free Software Foundation, either version 3 of the License, or");
  v.push_back("(at your option) any later version.");
  v.push_back("");
  v.push_back("This program is distributed in the hope that it will be useful,");
  v.push_back("but WITHOUT ANY WARRANTY; without even the implied warranty of");
  v.push_back("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the");
  v.push_back("GNU General Public License for more details.");
  v.push_back("You should have received a copy of the GNU General Public License");
  v.push_back("along with this program.If not, see <http://www.gnu.org/licenses/>.");
  return v;
}
//---------------------------------------------------------------------------
