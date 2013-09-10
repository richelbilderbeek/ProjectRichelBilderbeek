//---------------------------------------------------------------------------
/*
QtCreatorProFile, class to parse Qt Project files
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtCreatorProFile.htm
//---------------------------------------------------------------------------
#ifndef QTCREATORPROFILE_H
#define QTCREATORPROFILE_H

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "about.h"
#pragma GCC diagnostic pop

namespace ribi {

///QtCreatorProFile parses .pro files
struct QtCreatorProFile : public boost::noncopyable
{
  ///Parse a .pro file
  explicit QtCreatorProFile(const std::string& filename);

  ///Obtain this class its About information
  static const ribi::About GetAbout();

  ///Obtain the CONFIG
  const std::set<std::string>& GetConfig() const { return m_config; }

  ///Obtain the DEFINES
  const std::set<std::string>& GetDefines() const { return m_defines; }

  ///Obtain the FORMS
  const std::set<std::string>& GetForms() const { return m_forms; }

  ///Obtain the HEADERS
  const std::set<std::string>& GetHeaders() const { return m_headers; }

  ///Obtain the INCLUDEPATH
  const std::set<std::string>& GetIncludepath() const { return m_includepath; }

  ///Obtain the LIBS
  const std::set<std::string>& GetLibs() const { return m_libs; }

  ///Obtain the OTHER_FILES
  const std::set<std::string>& GetOtherFiles() const { return m_other_files; }

  ///Get the project file its file name
  const std::string& GetQtCreatorProFilename() const { return m_pro_filename; }

  ///Obtain the QMAKE_CXXFLAGS
  const std::set<std::string>& GetQmakeCxxflags() const { return m_qmake_cxxflags; }

  ///Obtain the QT
  const std::set<std::string>& GetQt() const { return m_qt; }

  ///Obtain the RESOURCES
  const std::set<std::string>& GetResources() const { return m_resources; }

  ///Obtain the SOURCES
  const std::set<std::string>& GetSources() const  { return m_sources; }

  ///Obtain the TARGET
  const std::set<std::string>& GetTarget() const { return m_target; }

  ///Obtain the TEMPLATE
  const std::set<std::string>& GetTemplate() const { return m_template; }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Set the CONFIG
  void SetConfig(const std::set<std::string>& s) { m_config = s; }

  ///Set the DEFINES
  void SetDefines(const std::set<std::string>& s) { m_defines = s; }

  ///Set the FORMS
  void SetForms(const std::set<std::string>& s) { m_forms = s; }

  ///Set the HEADERS
  void SetHeaders(const std::set<std::string>& s) { m_headers = s; }

  ///Set the INCLUDEPATH
  void SetIncludepath(const std::set<std::string>& s) { m_includepath = s; }

  ///Set the LIBS
  void SetLibs(const std::set<std::string>& s) { m_libs = s; }

  ///Set the OTHER_FILES
  void SetOtherFiles(const std::set<std::string>& s) { m_other_files = s; }

  ///Set the project file its file name
  void SetQtCreatorProFilename(const std::string& s) { m_pro_filename = s; }

  ///Set the QMAKE_CXXFLAGS
  void SetQmakeCxxflags(const std::set<std::string>& s) { m_qmake_cxxflags = s; }

  ///Set the QT
  void SetQt(const std::set<std::string>& s) { m_qt = s; }

  ///Set the RESOURCES
  void SetResources(const std::set<std::string>& s) { m_resources = s; }

  ///Set the SOURCES
  void SetSources(const std::set<std::string>& s)  { m_sources = s; }

  ///Set the TARGET
  void SetTarget(const std::set<std::string>& s) { m_target = s; }

  ///Set the TEMPLATE
  void SetTemplate(const std::set<std::string>& s) { m_template = s; }

  private:
  ///Be sure the class is correctly deleted
  ~QtCreatorProFile() {}
  friend void boost::checked_delete<>(QtCreatorProFile* x);

  ///The items at CONFIG
  std::set<std::string> m_config;

  ///The items at DEFINES
  std::set<std::string> m_defines;

  ///The items at FORMS
  std::set<std::string> m_forms;

  ///The items at HEADERS
  std::set<std::string> m_headers;

  ///The items at INCLUDEPATH
  std::set<std::string> m_includepath;

  ///The items at LIBS
  std::set<std::string> m_libs;

  ///The items at OTHER_FILES
  std::set<std::string> m_other_files;

  ///The .pro file to parse
  std::string m_pro_filename;

  ///The items at QMAKE_CXXFLAGS
  std::set<std::string> m_qmake_cxxflags;

  ///The items at QT
  std::set<std::string> m_qt;

  ///The items at RESOURCES
  std::set<std::string> m_resources;

  ///The item at TARGET
  std::set<std::string> m_target;

  ///The items at TEMPLATE
  std::set<std::string> m_template;

  ///The items at SOURCES
  std::set<std::string> m_sources;

  ///FileToVector reads a file and converts it to a std::vector<std::string>
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& filename);

  #ifndef NDEBUG
  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  static bool IsRegularFile(const std::string& filename);
  #endif

  ///Parse the .pro file its content, split into lines
  void Parse(const std::vector<std::string>& v);

  ///From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input, const char seperator);

  #ifndef NDEBUG
  ///Test QtCreatorProFile
  static void Test();
  #endif

  friend std::ostream& operator<<(std::ostream& os, const QtCreatorProFile& p);
  friend bool operator==(const QtCreatorProFile& lhs, const QtCreatorProFile& rhs);

};

std::ostream& operator<<(std::ostream& os, const QtCreatorProFile& p);
std::ostream& operator<<(std::ostream& os, const boost::shared_ptr<QtCreatorProFile>& p);
std::ostream& operator<<(std::ostream& os, const boost::shared_ptr<const QtCreatorProFile>& p);
bool operator==(const QtCreatorProFile& lhs, const QtCreatorProFile& rhs);

} //~namespace ribi

#endif // QTCREATORPROFILE_H
