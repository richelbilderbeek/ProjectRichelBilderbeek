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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtcreatorprofilezipscript.h"

#include <fstream>
#include <functional>
#include <iterator>
#include <set>

#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <QDir>

#include "fileio.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "trace.h"
#pragma GCC diagnostic pop

struct PathOrdering
{
  bool operator()(const std::string& lhs, const std::string& rhs)
  {
    //Shortest files first
    if (lhs.size() < rhs.size()) return true;
    //Order same-length files alphabetically
    if (lhs.size() == rhs.size() && lhs < rhs) return true;
    return false;
  }
};


ribi::QtCreatorProFileZipScript::QtCreatorProFileZipScript(
  const boost::shared_ptr<const QtCreatorProFile> pro_file)
  : m_filenames(ExtractFilenames(pro_file)),
    m_pro_file_name(pro_file->GetQtCreatorProFilename())

{
  #ifndef NDEBUG
  ribi::QtCreatorProFileZipScript::Test();
  assert(fileio::FileIo().IsUnixPath(m_pro_file_name));
  assert(pro_file);
  for (auto s: m_filenames)
  {
    assert(ribi::fileio::FileIo().IsRegularFile(s));
  }
  #endif
}

ribi::QtCreatorProFileZipScript::QtCreatorProFileZipScript(
  const std::set<std::string>& filenames,
  const std::string& pro_file_name)
  : m_filenames(filenames),
    m_pro_file_name(pro_file_name)
{

}

std::vector<boost::shared_ptr<ribi::QtCreatorProFile> > ribi::QtCreatorProFileZipScript::CreateProFiles(
  const std::vector<std::string>& filenames)
{
  std::vector<boost::shared_ptr<ribi::QtCreatorProFile> > pro_files;
  for (const std::string& filename: filenames)
  {
    assert(ribi::fileio::FileIo().IsRegularFile(filename));
    const boost::shared_ptr<ribi::QtCreatorProFile> pro_file(new ribi::QtCreatorProFile(filename));
    assert(pro_file);
    pro_files.push_back(pro_file);
  }
  return pro_files;
}

std::string ribi::QtCreatorProFileZipScript::CreateScript(const std::string& source_folder)
{
  if (!fileio::FileIo().IsFolder(source_folder))
  {
    std::stringstream s;
    s << "QtCreatorProFileZipScript::CreateScript: folder '" << source_folder << "' not found";
    throw std::runtime_error(s.str().c_str());
  }
  if (source_folder.find('\\') != std::string::npos)
  {
    std::stringstream s;
    s << "QtCreatorProFileZipScript::CreateScript: folder '" << source_folder << "' contains Windows"
      << "path seperators. Use slash instead of backslash";
    throw std::runtime_error(s.str().c_str());
  }
  if (source_folder.substr(0,6) != "../../")
  {
    std::stringstream s;
    s << "QtCreatorProFileZipScript::CreateScript: folder '" << source_folder << "' does"
      << "not start with '../../'. Change the folder's name accordingly";
    throw std::runtime_error(s.str().c_str());
  }
  assert(fileio::FileIo().IsFolder(source_folder));
  assert(source_folder.substr(0,6) == "../../");
  assert(fileio::FileIo().IsUnixPath(source_folder));

  //Also include .pri files in that folder
  std::vector<std::string> pro_filenames = GetProAndPriFilesInFolder(source_folder);

  //Add the .pri files in the .pro files
  {
    std::vector<std::string> w(pro_filenames);
    for (const std::string pro_filename: pro_filenames)
    {
      assert(ribi::fileio::FileIo().IsUnixPath(pro_filename));

      const std::string full_pro_filename
        = source_folder.empty()
        ? std::string()
        : source_folder + '/' + pro_filename
      ;
      #ifndef NDEBUG
      if (!ribi::fileio::FileIo().IsRegularFile(full_pro_filename))
      {
        TRACE("ERROR");
        TRACE(full_pro_filename);
      }
      #endif
      assert(ribi::fileio::FileIo().IsRegularFile(full_pro_filename));
      assert(ribi::fileio::FileIo().IsUnixPath(full_pro_filename));

      const boost::shared_ptr<QtCreatorProFile> pro_file(
        new QtCreatorProFile(full_pro_filename)
      );

      assert(pro_file);
      //Copy its .pri files to be scanned
      for (const std::string pri_file: pro_file->GetPriFiles())
      {
        assert(ribi::fileio::FileIo().IsUnixPath(pri_file));
        w.push_back(pri_file);
      }
    }
    std::swap(w,pro_filenames);
  }

  //Create the scripts by merging QtCreatorProFiles
  std::vector<boost::shared_ptr<const QtCreatorProFileZipScript>> scripts;

  for (const std::string& pro_filename: pro_filenames)
  {
    assert(ribi::fileio::FileIo().IsUnixPath(pro_filename));

    const std::string full_pro_filename
      = fileio::FileIo().SimplifyPath(
        source_folder
      + '/'
      + pro_filename
      )
    ;
    #ifndef NDEBUG
    if (!ribi::fileio::FileIo().IsRegularFile(full_pro_filename))
    {
      TRACE("ERROR");
      TRACE(full_pro_filename);
      TRACE(source_folder);
      TRACE(pro_filename);
      TRACE("BREAK");
    }
    if (!ribi::fileio::FileIo().IsUnixPath(full_pro_filename))
    {
      TRACE("ERROR");
      TRACE(full_pro_filename);
      TRACE(source_folder);
      TRACE(pro_filename);
      TRACE("BREAK");
    }
    #endif

    assert(ribi::fileio::FileIo().IsRegularFile(full_pro_filename));
    assert(fileio::FileIo().IsUnixPath(full_pro_filename));
    const boost::shared_ptr<QtCreatorProFile> pro_file(
      new QtCreatorProFile(full_pro_filename));
    assert(pro_file);

    const boost::shared_ptr<QtCreatorProFileZipScript> script(
      new QtCreatorProFileZipScript(pro_file));
    assert(script);

    scripts.push_back(script);
  }


  const boost::shared_ptr<QtCreatorProFileZipScript> merged_script
    = ribi::QtCreatorProFileZipScript::Merge(scripts);
  if (!merged_script)
  {
    return "Folder does not contain any .pro files";
  }
  else
  {
    std::stringstream script;
    script << *merged_script;
    return script.str();
  }
}


const std::set<std::string> ribi::QtCreatorProFileZipScript::ExtractFilenames(
  const boost::shared_ptr<const QtCreatorProFile>& pro_file) const
{
  assert(pro_file);

  std::vector<std::string> v;
  std::copy(pro_file->GetForms().begin(),pro_file->GetForms().end(),std::back_inserter(v));
  std::copy(pro_file->GetHeaders().begin(),pro_file->GetHeaders().end(),std::back_inserter(v));
  std::copy(pro_file->GetOtherFiles().begin(),pro_file->GetOtherFiles().end(),std::back_inserter(v));
  std::copy(pro_file->GetResources().begin(),pro_file->GetResources().end(),std::back_inserter(v));
  std::copy(pro_file->GetSources().begin(),pro_file->GetSources().end(),std::back_inserter(v));


  //Copy all resources
  for (const std::string qrc_filename_raw: pro_file->GetResources())
  {
    assert(ribi::fileio::FileIo().IsUnixPath(qrc_filename_raw));

    const std::string qrc_filename_full
        = qrc_filename_raw.size() < 7 || qrc_filename_raw.substr(0,6) != "../../"
        ? ribi::fileio::FileIo().GetPath(pro_file->GetQtCreatorProFilename())
        //? boost::filesystem::path(pro_file->GetQtCreatorProFilename()).parent_path().string()
            + "/" + qrc_filename_raw
        : qrc_filename_raw;

    assert(qrc_filename_full.size() > 6);
    assert(qrc_filename_full.substr(0,6) == "../../");
    assert(ribi::fileio::FileIo().IsUnixPath(qrc_filename_full));

    if (!ribi::fileio::FileIo().IsRegularFile(qrc_filename_full))
    {
      const std::string s = "Warning: Resource file \'" + qrc_filename_full + "\' not found";
      TRACE(s);
      continue;
    }
    assert(ribi::fileio::FileIo().IsRegularFile(qrc_filename_full));
    assert(qrc_filename_full.size() > 6 && qrc_filename_full.substr(0,6) == "../../");
    assert(qrc_filename_full.size() > 7 && qrc_filename_full.substr(0,7) != "../../.");
    const boost::shared_ptr<const QrcFile> qrc_file(
      new QrcFile(qrc_filename_full));
    assert(qrc_file);

    //BUG: QrcFile supplies its files without a full path
    //std::copy(qrc_file->GetFiles().begin(),qrc_file->GetFiles().end(),std::back_inserter(v));

    for (const std::string& filename : qrc_file->GetFiles())
    {
      assert(ribi::fileio::FileIo().IsUnixPath(filename));

      const std::string full_resource_item_name
        = ribi::fileio::FileIo().GetPath(qrc_filename_full) + "/" + filename;
      //  = boost::filesystem::path(qrc_filename_full).parent_path().string() + "/" + filename;

      assert(ribi::fileio::FileIo().IsRegularFile(full_resource_item_name));
      assert(ribi::fileio::FileIo().IsUnixPath(full_resource_item_name));

      v.push_back(full_resource_item_name);
    }
  }

  //Add paths if needed
  std::vector<std::string> filenames;
  assert(pro_file);
  assert(ribi::fileio::FileIo().IsRegularFile(pro_file->GetQtCreatorProFilename()));
  filenames.push_back(pro_file->GetQtCreatorProFilename());
  for (const std::string filename: v)
  {
    if (!filename.empty() && (filename[0] == '/' || filename[0] == '.'))
    {
      #ifndef NDEBUG
      if (!ribi::fileio::FileIo().IsRegularFile(filename))
      {
        TRACE("ERROR");
        TRACE(filename);
        TRACE("BREAK");
      }
      #endif
      assert(ribi::fileio::FileIo().IsRegularFile(filename));
      assert(ribi::fileio::FileIo().IsUnixPath(filename));
      filenames.push_back(filename);
    }
    else if (!filename.empty() && filename[0] != '/' && filename[0] != '.')
    {
      //Add full path
      const std::string s
        = ribi::fileio::FileIo().GetPath(pro_file->GetQtCreatorProFilename());
      //  = boost::filesystem::path(pro_file->GetQtCreatorProFilename()).parent_path().string();

      assert(s.size() > 6);
      assert(ribi::fileio::FileIo().IsUnixPath(s));

      const std::string t = s + "/" + filename;
      //TRACE(t);
      assert(ribi::fileio::FileIo().IsRegularFile(t));
      assert(ribi::fileio::FileIo().IsUnixPath(t));
      filenames.push_back(t);
    }
  }
  for (const auto s: filenames) { assert(ribi::fileio::FileIo().IsRegularFile(s)); }
  for (std::string& s: filenames) { s = fileio::FileIo().SimplifyPath(s); }
  for (const auto s: filenames) { assert(ribi::fileio::FileIo().IsRegularFile(s)); }
  std::sort(filenames.begin(),filenames.end());
  filenames.erase( std::unique(filenames.begin(),filenames.end()), filenames.end() );

  std::set<std::string> s;
  std::copy(filenames.begin(),filenames.end(),std::inserter(s,s.begin()));
  return s;
}

ribi::About ribi::QtCreatorProFileZipScript::GetAbout() noexcept
{
  ribi::About a(
    "Richel Bilderbeek",
    "QtCreatorProFileZipScript",
    "class to create a zip file from a .pro file",
    "the 19th of May 2013",
    "2013-2014",
    "http://www.richelbilderbeek.nl/CppQtCreatorProFileZipScript.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

//std::vector<std::string> ribi::QtCreatorProFileZipScript::GetProFilesInFolder(const std::string& folder)
//{
//  assert(fileio::FileIo().IsFolder(folder));
//  return ribi::fileio::FileIo().GetFilesInFolderByRegex(folder,".*\\.(pro)\\>");
//}

std::vector<std::string> ribi::QtCreatorProFileZipScript::GetProAndPriFilesInFolder(const std::string& folder)
{
  assert(fileio::FileIo().IsFolder(folder));
  const std::vector<std::string> v = ribi::fileio::FileIo().GetFilesInFolderByRegex(folder,".*\\.(pro|pri)\\>");
  return v;
}

std::string ribi::QtCreatorProFileZipScript::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::QtCreatorProFileZipScript::GetVersionHistory() noexcept
{
  return {
    "2013-05-19: version 1.0: initial version",
    "2013-08-19: version 1.1: replaced Boost.Regex by Boost.Xpressive",
    "2013-12-05: version 1.2: add support for .pri files"
    "2014-04-25: version 1.3: fixed SimplifiedPath bug",
    "2014-05-02: version 2.0: use UNIX path seperators only"
  };
}

boost::shared_ptr<ribi::QtCreatorProFileZipScript> ribi::QtCreatorProFileZipScript::Merge(
  const std::vector<boost::shared_ptr<const QtCreatorProFileZipScript> >& scripts)
{
  boost::shared_ptr<ribi::QtCreatorProFileZipScript> p;
  if (scripts.empty()) return p;

  std::set<std::string> all_filenames;
  std::string pro_file_name;

  for (const boost::shared_ptr<const QtCreatorProFileZipScript>& script: scripts)
  {
    const auto filenames = script->GetFilenames();
    all_filenames.insert(filenames.begin(),filenames.end());
    pro_file_name = script->GetProFileName(); //Just for having something
  }
  p.reset(new QtCreatorProFileZipScript(all_filenames,pro_file_name));
  assert(p);
  return p;
}


#ifndef NDEBUG
void ribi::QtCreatorProFileZipScript::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtCreatorProFileZipScript::Test");
  //Test basic functions on this project with going two folders down
  const std::vector<std::string> pro_file_names
    =
    {
      "../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro",
      "../../Tools/ToolCodeToHtml/ToolCodeToHtmlDesktop.pro",
      "../../Tools/ToolKalmanFilterer/ToolKalmanFiltererDesktop.pro",
      "../../ProjectRichelBilderbeek/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pro"
    };
  for (const std::string& pro_file_name: pro_file_names)
  {
    if (!ribi::fileio::FileIo().IsRegularFile(pro_file_name)) continue;

    assert(ribi::fileio::FileIo().IsRegularFile(pro_file_name));
    const boost::shared_ptr<const QtCreatorProFile> pro_file(
      new QtCreatorProFile(pro_file_name) );
    assert(pro_file);

    const boost::shared_ptr<const QtCreatorProFileZipScript> zip_script(
      new QtCreatorProFileZipScript(pro_file) );
    assert(zip_script);

    const std::set<std::string> filenames = zip_script->GetFilenames();
    for (const std::string& filename: filenames)
    {
      if (!ribi::fileio::FileIo().IsRegularFile(filename))
      {
        const std::string warning = "Warning: file \'" + filename + "\' not found";
        TRACE(warning);
        continue;
      }
      assert(ribi::fileio::FileIo().IsRegularFile(filename));
    }
  }
  //Test that GetProFilesInFolder detects an additional .pro file
  //being added to a folder
  {
    const std::string tmp_pro_filename { fileio::FileIo().GetTempFileName(".pro") };

    //Count the current number of .pro files
    const std::size_t n = GetProAndPriFilesInFolder("").size();

    //Add a .pro file
    {
      std::ofstream f(tmp_pro_filename.c_str());
      f.close();
      assert(ribi::fileio::FileIo().IsRegularFile(tmp_pro_filename));
    }

    //Count the current number of .pro and .pri files again
    const std::size_t p = GetProAndPriFilesInFolder("").size();
    #ifndef NDEBUG
    if (n != p-1)
    {
      TRACE("ERROR: GetProFilesInFolder does not detect .pro files correctly");
    }
    #endif
    assert(n == p - 1);
    fileio::FileIo().DeleteFile(tmp_pro_filename);
    const std::size_t q = GetProAndPriFilesInFolder("").size();
    assert(n == q);
  }
  TRACE("Finished ribi::QtCreatorProFileZipScript::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os,const QtCreatorProFileZipScript& script) noexcept
{
  #ifndef NDEBUG
  {
    const std::string s = script.GetProFileName();
    assert(s.size() > 6);
    assert(s.substr(0,6) == "../../");
    assert(ribi::fileio::FileIo().IsUnixPath(s));
  }
  #endif


  os << "#!/bin/sh" << '\n';
  os << "# Created from file '"
     << script.GetProFileName()
     << "\'" << '\n';
  os << '\n';

  //if (!m_folder_name_for_sloccount.empty())
  //{
  //  os << '\n'
  //     << "echo \"Creating a sloccount file\"" << '\n'
  //     << "sloccount " << m_folder_name_for_sloccount << " > sloccount.txt" << '\n'
  //     << '\n';
  //}
  //if (!m_doxygen_filename.empty())
  //{
  //  os << "echo \"Creating documentation\"" << '\n'
  //     << "doxygen \"" << m_doxygen_filename << "\"" << '\n';
  //}
  //os << '\n';
  //os << "echo \"Removing user information\"" << '\n';
  //os << "rm *.user" << '\n';
  //os << '\n';
  //os << "echo \"Removing possible temp file\"" << '\n';
  //os << "rm copy.txt" << '\n';
  //os << "rm tmp.txt" << '\n';
  //os << '\n';

  os << "echo \"Creating of all folders\"" << '\n';
  os << '\n';
  os << "mkdir Projects" << '\n';

  //file names with full path
  const auto file_names_vector = script.GetFilenames();
  const std::set<std::string,PathOrdering> file_names(
    file_names_vector.begin(),file_names_vector.end()
  );

  std::set<std::string,PathOrdering> folder_names;
  //Add the folders added by the .pro file
  for (const std::string filename: file_names)
  {
    assert(ribi::fileio::FileIo().IsRegularFile(filename));
    assert(ribi::fileio::FileIo().IsUnixPath(filename));

    std::string s = ribi::fileio::FileIo().GetPath(filename);
    TRACE(s);
    while (!s.empty())
    {
      const std::size_t old_len = s.size();
      if (!(s[ s.size() - 1] != '.' || s[ s.size() - 2] != '.'))
      {
        TRACE(s);
        TRACE(filename);
        TRACE("ERROR");
      }
      //assert(s[ s.size() - 1] != '.' || s[ s.size() - 2] != '.');
      const std::string t = fileio::FileIo().SimplifyPath(s);
      folder_names.insert(t);
      s = ribi::fileio::FileIo().GetPath(s);
      assert(fileio::FileIo().IsUnixPath(s));
      const std::size_t new_len = s.size();
      if (new_len == old_len) { s = ""; }
    }
  }


  for (const std::string& s: folder_names)
  {
    if (s.size() > 6 && s.substr(0,6) == "../../")
    {
      const std::string folder = s.substr(6,s.size() - 6);
      assert(ribi::fileio::FileIo().IsUnixPath(folder));
      if ( folder[ folder.size() - 1] == '.'
        || folder[ folder.size() - 2] == '.'
      )
      {
        TRACE("ERROR");
        TRACE(folder);
        TRACE("BREAK");
      }
      assert(folder[ folder.size() - 1] != '.');
      assert(folder[ folder.size() - 2] != '.');
      assert(folder[ folder.size() - 3] != '.');
      assert(folder[ folder.size() - 4] != '.');
      os << "mkdir Projects" << fileio::FileIo().GetPathSeperator() << folder << '\n';
    }
  }

  os << '\n';
  os << "echo \"Copying files\"" << '\n';
  os << '\n';

  for (const std::string& s: file_names)
  {
    assert(ribi::fileio::FileIo().IsUnixPath(s));

    if (s.size() > 6 && s.substr(0,6) == "../../")
    {
      os << "cp " << s << " Projects/" << s.substr(6,s.size() - 6) << '\n';
    }
    else if (s.size() > 3 && s.substr(0,1) != ".")
    {
      //A file in the .pro file its folder
      os << "cp " << s << " Projects/"
        << ribi::fileio::FileIo().GetPath(script.GetProFileName())
        << s << '\n'
      ;
    }
  }

  os << '\n';
  os << "FILENAME=\""
     << ribi::fileio::FileIo().GetPath( script.GetProFileName() )
     //<< boost::filesystem::path( script.GetProFileName() ).parent_path().string()
     << "Source\"" << '\n';
  os << "ZIP_FILENAME=$FILENAME\".zip\"" << '\n';
  os << '\n';
  os << "echo \"Compressing files\"" << '\n';
  os << '\n';
  os << "zip -r $FILENAME Projects" << '\n';
  os << '\n';
  os << "echo \"Cleaning up\"" << '\n';
  os << '\n';
  os << "echo \"Emptying subfolders\"" << '\n';
  os << '\n';

  std::for_each(folder_names.rbegin(),folder_names.rend(),
    [&os](const std::string& s)
    {
      if (s.size() > 6 && s.substr(0,6) == "../../")
      {
         os << "rm Projects/" + s.substr(6,s.size() - 6) << "/*.*" << '\n';
      }
    }
  );

  os << "rm Projects/*.*" << '\n';

  std::for_each(folder_names.rbegin(),folder_names.rend(),
    [&os](const std::string& s)
    {
      if (s.size() > 6 && s.substr(0,6) == "../../")
      {
        os << "rmdir Projects/" << s.substr(6,s.size()-6) << '\n';
      }
    }
  );
  os << "rmdir Projects" << '\n';
  os << '\n';
  os << "echo \"Done\"" << '\n';
  os << '\n';
  {
    const std::vector<std::string> w
      = ribi::QtCreatorProFileZipScript::GetAbout().CreateAboutText();
    std::transform(w.begin(),w.end(),
    std::ostream_iterator<std::string>(os,"\n"),
      [](const std::string& s)
      {
        return "# " + s;
      }
    );
  }
  return os;
}
