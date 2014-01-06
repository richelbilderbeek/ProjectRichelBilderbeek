//---------------------------------------------------------------------------
/*
About, class for containing information about a program
Copyright (C) 2010-2014 Richel Bilderbeek

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
#ifndef ABOUT_H
#define ABOUT_H

#include <iosfwd>
#include <string>
#include <vector>

namespace ribi {

///About is a class to contain 'about' information
struct About
{
  explicit About(
    const std::string author,
    const std::string file_title,
    const std::string file_description,
    const std::string programmed_on,
    const std::string years,
    const std::string url,
    const std::string version,
    const std::vector<std::string>& version_history) noexcept;

  ///Add a library name and version
  void AddLibrary(const std::string& s) noexcept;

  ///Create the 'about' text
  const std::vector<std::string> CreateAboutText() const noexcept;

  ///Create a version history
  const std::vector<std::string> CreateVersionHistory() const noexcept;

  ///Create a text with all libraries used
  const std::vector<std::string> CreateLibrariesUsedText() const noexcept;

  ///CreateLicence creates a GPL 3.0 licence.
  const std::vector<std::string> CreateLicenceText() const noexcept;

  ///Obtain the version of this About class itself
  static const std::string GetAboutVersion() noexcept;

  ///Obtain the version history of this About class itself
  static const std::vector<std::string> GetAboutVersionHistory() noexcept;

  ///Get the author of this class
  const std::string& GetAuthor() const noexcept { return m_author; }

  ///GetBoostVersion returns the version of the current Boost library.
  ///From http://www.richelbilderbeek.nl/CppGetBoostVersion.htm
  static const std::string GetBoostVersion() noexcept;

  ///Get the author of my classes
  static const std::string GetDefaultAuthor() noexcept { return "Richel Bilderbeek"; }

  ///Get the file/class/program its description
  const std::string& GetFileDescription() const noexcept { return m_file_description; }

  ///Get the file/class/program its title
  const std::string& GetFileTitle() const noexcept { return m_file_title; }

  ///Get the date this class has been programmed on
  const std::string& GetProgrammedAt() const noexcept { return m_programmed_on; }

  ///GetQtCreatorVersion returns the version number of the Qt Creator currently installed.
  ///From http://www.richelbilderbeek.nl/CppGetQtCreatorVersion.htm
  static const std::string GetQtCreatorVersion() noexcept;

  ///GetStlVersion returns the version number of the GCC STL currently installed.
  ///From http://www.richelbilderbeek.nl/CppGetStlVersion.htm
  static const std::string GetStlVersion() noexcept;

  ///Get the URL this class can be downloaded from
  const std::string& GetUrl() const noexcept { return m_url; }

  ///Obtain the years this class has been worked on
  const std::string& GetYears() const noexcept { return m_years; }

  ///Obtain the version of this class
  const std::string& GetVersion() const noexcept { return m_version; }

  private:

  ///The author of this class
  const std::string m_author;

  ///The title or name of this class
  const std::string m_file_title;

  ///The description of this class
  const std::string m_file_description;

  ///The libraries and/or classes used by this class
  std::vector<std::string> m_libraries;

  ///The date this class was programmed
  const std::string m_programmed_on;

  ///The years this class has been worked on
  const std::string m_years;

  ///The URL this class can be downloaded from
  const std::string m_url;

  ///The version of this class
  const std::string m_version;

  ///The version history of this class
  const std::vector<std::string> m_version_history;

};

std::ostream& operator<<(std::ostream& os,const About& a) noexcept;

} //~namespace ribi

#endif // ABOUT_H
