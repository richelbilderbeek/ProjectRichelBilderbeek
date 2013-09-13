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
#ifndef QTCREATORPROFILEZIPSCRIPT
#define QTCREATORPROFILEZIPSCRIPT

#include <set>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "qtcreatorprofile.h"
#pragma GCC diagnostic pop

namespace ribi {

///Create a shell script to zip a Qt Creator .pro file
struct QtCreatorProFileZipScript
{
  QtCreatorProFileZipScript(
    const boost::shared_ptr<const ribi::QtCreatorProFile> pro_file
  );
  QtCreatorProFileZipScript(const QtCreatorProFileZipScript&) = delete;
  QtCreatorProFileZipScript& operator=(const QtCreatorProFileZipScript&) = delete;

  ///Create a script to zip all .pro files (and all they refer to) in a folder
  static const std::string CreateScript(const std::string& source_folder);

  ///Obtain this class its About information
  static const About GetAbout();

  ///Obtain all filenames
  const std::set<std::string>& GetFilenames() const { return m_filenames; }

  ///Obtain the .pro file
  //const boost::shared_ptr<const QtCreatorProFile> GetProFile() const { return m_pro_file; }
  const std::string& GetProFileName() const { return m_pro_file_name; }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  static const boost::shared_ptr<QtCreatorProFileZipScript> Merge(
    const std::vector<boost::shared_ptr<const QtCreatorProFileZipScript> >& v);

  ///Set all filenames
  void SetFilenames(const std::set<std::string>& filenames) { m_filenames = filenames; }

  private:
  ///Used when merging
  QtCreatorProFileZipScript(
    const std::set<std::string>& filenames,
    const std::string& pro_file_name);

  ///Be sure the class is correctly deleted
  ~QtCreatorProFileZipScript() {}
  friend void boost::checked_delete<>(QtCreatorProFileZipScript* x);

  ///All the files used by the QtCreatorProFile
  std::set<std::string> m_filenames;

  ///The original .pro file its filename
  const std::string m_pro_file_name;
  //const boost::shared_ptr<const QtCreatorProFile> m_pro_file;

  ///Create a QtCreatorProFile from every filename
  static const std::vector<boost::shared_ptr<QtCreatorProFile> > CreateProFiles(const std::vector<std::string>& pro_files);

  ///Extract a QtCreatorProFile its filenames
  const std::set<std::string> ExtractFilenames(
    const boost::shared_ptr<const QtCreatorProFile> & pro_file) const;

  ///Get all the files in a folder
  static const std::vector<std::string> GetFilesInFolder(const std::string& folder);

  ///Returns the path of a filename
  ///From http://www.richelbilderbeek.nl/CppGetPath.htm
  static const std::string GetPath(const std::string& filename);

  ///Get all the .pro files in a folder
  //From http://www.richelbilderbeek.nl/CppGetProFilesInFolder.htm
  static const std::vector<std::string> GetProFilesInFolder(const std::string& folder);

  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  static bool IsRegularFile(const std::string& filename);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif

  friend std::ostream& operator<<(std::ostream& os,const QtCreatorProFileZipScript& script);
};

///Write the script to a stream
std::ostream& operator<<(std::ostream& os,const QtCreatorProFileZipScript& script);

} //~namespace ribi

#endif // QTCREATORPROFILEZIPSCRIPT
