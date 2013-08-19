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
#ifndef QRCFILE_H
#define QRCFILE_H

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

#include "about.h"

///QrcFile parses Qt resource (.qrc) files
struct QrcFile
{
  ///Parse a .qrc file
  explicit QrcFile(const std::string& filename);

  ///Obtain this class its About information
  static const About GetAbout();

  ///Obtain the items between <file> and </file>
  const std::set<std::string>& GetFiles() const { return m_files; }

  ///Get the project file its file name
  const std::string& GetQrcFilename() const { return m_qrc_filename; }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Test QrcFile
  static void Test();

  private:
  ///The items between <file> and </file>
  std::set<std::string> m_files;

  ///The .qrc file to parse
  std::string m_qrc_filename;

  ///FileExists checks if a certain file exists
  ///From http://www.richelbilderbeek.nl/CppFileExists.htm
  static bool FileExists(const std::string& filename);

  ///FileToVector reads a file and converts it to a std::vector<std::string>
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& filename);

  friend std::ostream& operator<<(std::ostream& os, const QrcFile& f);
};

std::ostream& operator<<(std::ostream& os, const QrcFile& f);

#endif // QRCFILE_H
