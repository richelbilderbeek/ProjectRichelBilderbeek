//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#ifndef CREATEQTPROJECTZIPFILEPATH_H
#define CREATEQTPROJECTZIPFILEPATH_H

#include <string>

namespace ribi {

namespace CreateQtProjectZipFile {

///Path is a tri-tuple
struct Path
{
  ///Constructs a Path from a path/
  ///For example,
  /// '/home/richel/Projects/Tools/ToolCreateQtProjectZipFile/toolcreatezipfiledesktop.pro'
  ///becomes
  /// - m_main_folder: Tools
  /// - m_sub_folder: ToolCreateQtProjectZipFile
  /// - m_filename: toolcreatezipfiledesktop.pro
  Path(const std::string& s);

  Path(const std::string& main_folder,const std::string& sub_folder, const std::string& filename);

  ///Extract the filename from a path.
  ///Examples:
  ///-'Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pro' -> 'ProjectRichelBilderbeekDesktop.pro'
  ///-'Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro' -> 'ToolCreateQtProjectZipFileDesktop.pro'
  static std::string ExtractFilename(const std::string& filename);

  ///Extract the main folder from a path.
  ///Examples:
  ///-'Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pro' -> 'Projects'
  ///-'Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro' -> 'Tools'
  static std::string ExtractMainFolder(const std::string& filename);

  ///Extract the sub-folder from a path.
  ///Examples:
  ///-'Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pro' -> 'ProjectRichelBilderbeek'
  ///-'Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro' -> 'ToolCreateQtProjectZipFile'
  static std::string ExtractSubFolder(const std::string& filename);

  ///Get the sub folder, e.g. 'ProjectRichelBilderbeekDesktop.pro', 'ToolCreateQtProjectZipFileDesktop.pro'
  const std::string& GetFilename() const { return m_filename; }

  ///Get the main folder, e.g. 'Projects', 'Tools'
  const std::string& GetMainFolder() const { return m_main_folder; }

  ///Get the sub folder, e.g. 'ProjectRichelBilderbeek', 'ToolCreateQtProjectZipFile'
  const std::string& GetSubFolder() const { return m_sub_folder; }

  ///Test if this Path has specified main folder and sub folder and filename
  bool IsComplete() const;

  ///Test if this Path can be found at ../../[main folder]/[sub folder]/[filename]
  bool IsPresent() const;

  ///Set the main folder, e.g. 'Projects', 'Tools'
  void SetMainFolder(const std::string& s);

  ///Set the sub folder, e.g. 'ProjectRichelBilderbeek', 'ToolCreateQtProjectZipFile'
  void SetSubFolder(const std::string& s);

  ///Test this class
  static void Test() noexcept;

  ///Converts a Path to a string
  ///For example,
  /// - m_main_folder: Tools
  /// - m_sub_folder: ToolCreateQtProjectZipFile
  /// - m_filename: toolcreatezipfiledesktop.pro
  ///becomes
  /// '/home/richel/Projects/Tools/ToolCreateQtProjectZipFile/toolcreatezipfiledesktop.pro'
  std::string ToStr() const;

  private:
  const std::string m_filename;
  std::string m_main_folder;
  std::string m_sub_folder;
};

} //~namespace CreateQtProjectZipFile

} //~namespace ribi

#endif // CREATEQTPROJECTZIPFILEPATH_H
