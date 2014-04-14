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
  #endif
  assert(pro_file);
  for (auto s: m_filenames) { assert(ribi::fileio::FileIo().IsRegularFile(s)); }
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
  assert(fileio::FileIo().IsFolder(source_folder));
  assert(source_folder.substr(0,6) == "../../");

  //Also include .pri files in that folder
  std::vector<std::string> pro_filenames = GetProAndPriFilesInFolder(source_folder);

  //Add the .pri files in the .pro files
  {
    std::vector<std::string> w(pro_filenames);
    for (const std::string pro_filename: pro_filenames)
    {

      const std::string full_pro_filename = (source_folder.empty() ? std::string() : source_folder + "/") + pro_filename;
      #ifndef NDEBUG
      if (!ribi::fileio::FileIo().IsRegularFile(full_pro_filename))
      {
        TRACE("ERROR");
        TRACE(full_pro_filename);
      }
      #endif
      assert(ribi::fileio::FileIo().IsRegularFile(full_pro_filename));
      const boost::shared_ptr<QtCreatorProFile> pro_file(
      new QtCreatorProFile(full_pro_filename));
      assert(pro_file);
      //Copy its .pri files to be scanned
      for (const std::string pri_file: pro_file->GetPriFiles())
      {
        w.push_back(pri_file);
      }
    }
    std::swap(w,pro_filenames);
  }

  //Create the scripts by merging QtCreatorProFiles
  std::vector<boost::shared_ptr<const QtCreatorProFileZipScript>> scripts;

  for (const std::string& pro_filename: pro_filenames)
  {
    const std::string full_pro_filename = source_folder + "/" + pro_filename;
    assert(ribi::fileio::FileIo().IsRegularFile(full_pro_filename));
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
    const std::string qrc_filename_full
        = qrc_filename_raw.size() < 7 || qrc_filename_raw.substr(0,6) != "../../"
        ? ribi::fileio::FileIo().GetPath(pro_file->GetQtCreatorProFilename())
        //? boost::filesystem::path(pro_file->GetQtCreatorProFilename()).parent_path().string()
            + "/" + qrc_filename_raw
        : qrc_filename_raw;

    assert(qrc_filename_full.size() > 6);
    assert(qrc_filename_full.substr(0,6) == "../../");

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
      const std::string full_resource_item_name
        = ribi::fileio::FileIo().GetPath(qrc_filename_full) + "/" + filename;
      //  = boost::filesystem::path(qrc_filename_full).parent_path().string() + "/" + filename;
      assert(ribi::fileio::FileIo().IsRegularFile(full_resource_item_name));
      v.push_back(full_resource_item_name);
    }
  }

  //Add paths if needed
  std::set<std::string> filenames;
  assert(pro_file);
  assert(ribi::fileio::FileIo().IsRegularFile(pro_file->GetQtCreatorProFilename()));
  filenames.insert(pro_file->GetQtCreatorProFilename());
  for (const std::string filename: v)
  {
    if (!filename.empty() && (filename[0] == '/' || filename[0] == '.'))
    {
      //TRACE(filename);
      assert(ribi::fileio::FileIo().IsRegularFile(filename));
      filenames.insert(filename);
    }
    else if (!filename.empty() && filename[0] != '/' && filename[0] != '.')
    {
      //Add full path
      const std::string s
        = ribi::fileio::FileIo().GetPath(pro_file->GetQtCreatorProFilename());
      //  = boost::filesystem::path(pro_file->GetQtCreatorProFilename()).parent_path().string();
      assert(s.size() > 6);
      const std::string t = s + "/" + filename;
      //TRACE(t);
      assert(ribi::fileio::FileIo().IsRegularFile(t));
      filenames.insert(t);
    }
  }
  for (auto s: m_filenames) { assert(ribi::fileio::FileIo().IsRegularFile(s)); }
  return filenames;
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
  return "1.2";
}

std::vector<std::string> ribi::QtCreatorProFileZipScript::GetVersionHistory() noexcept
{
  return {
    "2013-05-19: version 1.0: initial version",
    "2013-08-19: version 1.1: replaced Boost.Regex by Boost.Xpressive",
    "2013-12-05: version 1.2: add support for .pri files"
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
  assert(script.GetProFileName().size() > 6);
  assert(script.GetProFileName().substr(0,6) == "../../");

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
    std::string s = ribi::fileio::FileIo().GetPath(filename);
    while (!s.empty())
    {
      const std::size_t old_len = s.size();
      folder_names.insert(s);
      s = ribi::fileio::FileIo().GetPath(s);
      const std::size_t new_len = s.size();
      if (new_len == old_len) { s = ""; }
    }
  }


  for (const std::string& s: folder_names)
  {
    if (s.size() > 6 && s.substr(0,6) == "../../")
    {
      const std::string folder = s.substr(6,s.size() - 6);
      assert(folder[ folder.size() - 1] != '.');
      assert(folder[ folder.size() - 2] != '.');
      assert(folder[ folder.size() - 3] != '.');
      assert(folder[ folder.size() - 4] != '.');
      os << "mkdir Projects/" << folder << '\n';
    }
  }

  os << '\n';
  os << "echo \"Copying files\"" << '\n';
  os << '\n';

  for (const std::string& s: file_names)
  {
    if (s.size() > 6 && s.substr(0,6) == "../../")
    {
      os << "cp " << s << " Projects/" + s.substr(6,s.size() - 6) << '\n';
    }
    else if (s.size() > 3 && s.substr(0,1) != ".")
    {
      //A file in the .pro file its folder
      os << "cp " << s << " Projects/"
        //<< boost::filesystem::path(script.GetProFileName()).parent_path().string()
        << ribi::fileio::FileIo().GetPath(script.GetProFileName())
        << s
        << '\n';
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
