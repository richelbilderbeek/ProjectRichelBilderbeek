#ifndef QTCREATORPROFILEZIPSCRIPT
#define QTCREATORPROFILEZIPSCRIPT

#include <set>
#include <string>
#include <vector>

#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "qtcreatorprofile.h"

///Create a shell script to zip a Qt Creator .pro file
struct QtCreatorProFileZipScript : public boost::noncopyable
{
  QtCreatorProFileZipScript(
    const boost::shared_ptr<const QtCreatorProFile> pro_file);

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

  ///Get all the .pro files in a folder
  //From http://www.richelbilderbeek.nl/CppGetProFilesInFolder.htm
  static const std::vector<std::string> GetProFilesInFolder(const std::string& folder);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

///Write the script to a stream
std::ostream& operator<<(std::ostream& os,const QtCreatorProFileZipScript& script);

#endif // QTCREATORPROFILEZIPSCRIPT
