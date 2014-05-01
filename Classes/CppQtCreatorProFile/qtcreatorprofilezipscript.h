//---------------------------------------------------------------------------
/*
QtCreatorProFile, class to parse Qt Project files
Copyright (C) 2010-2014 Richel Bilderbeek

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
  static std::string CreateScript(const std::string& source_folder);

  ///Obtain this class its About information
  static About GetAbout() noexcept;

  ///Obtain all filenames
  const std::set<std::string>& GetFilenames() const { return m_filenames; }

  ///Obtain the .pro file
  //const boost::shared_ptr<const QtCreatorProFile> GetProFile() const { return m_pro_file; }
  const std::string& GetProFileName() const { return m_pro_file_name; }

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  static boost::shared_ptr<QtCreatorProFileZipScript> Merge(
    const std::vector<boost::shared_ptr<const QtCreatorProFileZipScript> >& v);

  ///Set all filenames
  void SetFilenames(const std::set<std::string>& filenames) { m_filenames = filenames; }

  private:
  ///Used when merging
  QtCreatorProFileZipScript(
    const std::set<std::string>& filenames,
    const std::string& pro_file_name);

  ///Be sure the class is correctly deleted
  ~QtCreatorProFileZipScript() noexcept {}
  friend void boost::checked_delete<>(QtCreatorProFileZipScript* x);

  ///All the files used by the QtCreatorProFile
  std::set<std::string> m_filenames;

  ///The original .pro file its filename
  const std::string m_pro_file_name;
  //const boost::shared_ptr<const QtCreatorProFile> m_pro_file;

  ///Create a QtCreatorProFile from every filename
  static std::vector<boost::shared_ptr<QtCreatorProFile> > CreateProFiles(const std::vector<std::string>& pro_files);

  ///Extract a QtCreatorProFile its filenames
  const std::set<std::string> ExtractFilenames(
    const boost::shared_ptr<const QtCreatorProFile> & pro_file) const;

  ///Get all the .pro files in a folder
  //From http://www.richelbilderbeek.nl/CppGetProFilesInFolder.htm

  static std::vector<std::string> GetProAndPriFilesInFolder(const std::string& folder);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os,const QtCreatorProFileZipScript& script) noexcept;
};

std::ostream& operator<<(std::ostream& os,const QtCreatorProFileZipScript& script) noexcept;

} //~namespace ribi

#endif // QTCREATORPROFILEZIPSCRIPT
