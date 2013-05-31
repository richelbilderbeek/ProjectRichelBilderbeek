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
#ifndef NDSMAKE_H
#define NDSMAKE_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include "../ToolTestProFile/profile.h"
//---------------------------------------------------------------------------
struct Ndsmake
{
  Ndsmake(const std::string filename);
  const std::string& GetCommand() const { return m_command; }
  static const std::vector<std::string> GetHelp();
  static const std::vector<std::string> GetHistory();
  static const std::vector<std::string> GetLicence();
  const ProFile& GetProFile() const { return m_proFile; }
  static std::string GetVersion() { return "1.2"; }
  private:
  /* const */ std::string m_command; //A terminal command
  const ProFile m_proFile;
  const std::string CreateCommand() const;
};
//---------------------------------------------------------------------------
#endif // NDSMAKE_H
