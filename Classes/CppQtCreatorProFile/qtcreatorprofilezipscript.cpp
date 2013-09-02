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
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtcreatorprofilezipscript.h"

#include <fstream>
#include <functional>
#include <iterator>
#include <set>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#pragma GCC diagnostic pop

#include <QDir>

#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "trace.h"

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


QtCreatorProFileZipScript::QtCreatorProFileZipScript(
  const boost::shared_ptr<const QtCreatorProFile> pro_file)
  : m_filenames(ExtractFilenames(pro_file)),
    m_pro_file_name(pro_file->GetQtCreatorProFilename())

{
  #ifndef NDEBUG
  QtCreatorProFileZipScript::Test();
  #endif
  assert(pro_file);
}

QtCreatorProFileZipScript::QtCreatorProFileZipScript(
  const std::set<std::string>& filenames,
  const std::string& pro_file_name)
  : m_filenames(filenames),
    m_pro_file_name(pro_file_name)
{

}

const std::vector<boost::shared_ptr<QtCreatorProFile> > QtCreatorProFileZipScript::CreateProFiles(
  const std::vector<std::string>& filenames)
{
  std::vector<boost::shared_ptr<QtCreatorProFile> > pro_files;
  for (const std::string& filename: filenames)
  {
    assert(IsRegularFile(filename));
    const boost::shared_ptr<QtCreatorProFile> pro_file(new QtCreatorProFile(filename));
    assert(pro_file);
    pro_files.push_back(pro_file);
  }
  return pro_files;
}

const std::string QtCreatorProFileZipScript::CreateScript(const std::string& source_folder)
{

  const std::vector<std::string> pro_filenames = GetProFilesInFolder(source_folder);

  std::vector<boost::shared_ptr<const QtCreatorProFileZipScript> > scripts;

  for (const std::string& pro_filename: pro_filenames)
  {
    const boost::shared_ptr<QtCreatorProFile> pro_file(
      new QtCreatorProFile(pro_filename));
    assert(pro_file);

    const boost::shared_ptr<QtCreatorProFileZipScript> script(
      new QtCreatorProFileZipScript(pro_file));
    assert(script);

    scripts.push_back(script);
  }


  const boost::shared_ptr<QtCreatorProFileZipScript> merged_script
    = QtCreatorProFileZipScript::Merge(scripts);
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


const std::set<std::string> QtCreatorProFileZipScript::ExtractFilenames(
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
        = qrc_filename_raw.size() < 7 || qrc_filename_raw.substr(0,6) != std::string("../../")
        ? GetPath(pro_file->GetQtCreatorProFilename())
        //? boost::filesystem::path(pro_file->GetQtCreatorProFilename()).parent_path().string()
            + "/" + qrc_filename_raw
        : qrc_filename_raw;

    assert(qrc_filename_full.size() > 6);
    assert(qrc_filename_full.substr(0,6) == std::string("../../"));

    if (!IsRegularFile(qrc_filename_full))
    {
      const std::string s = "Warning: Resource file \'" + qrc_filename_full + "\' not found";
      TRACE(s);
      continue;
    }
    assert(IsRegularFile(qrc_filename_full));
    assert(qrc_filename_full.size() > 6 && qrc_filename_full.substr(0,6) == std::string("../../"));
    assert(qrc_filename_full.size() > 7 && qrc_filename_full.substr(0,7) != std::string("../../."));
    const boost::shared_ptr<const QrcFile> qrc_file(
      new QrcFile(qrc_filename_full));
    assert(qrc_file);

    //BUG: QrcFile supplies its files without a full path
    //std::copy(qrc_file->GetFiles().begin(),qrc_file->GetFiles().end(),std::back_inserter(v));

    for (const std::string& filename : qrc_file->GetFiles())
    {
      const std::string full_resource_item_name
        = GetPath(qrc_filename_full) + "/" + filename;
      //  = boost::filesystem::path(qrc_filename_full).parent_path().string() + "/" + filename;
      assert(IsRegularFile(full_resource_item_name));
      v.push_back(full_resource_item_name);
    }
  }

  //Add paths if needed
  std::set<std::string> filenames;
  assert(pro_file);
  filenames.insert(pro_file->GetQtCreatorProFilename());
  for (const std::string filename: v)
  {
    if (!filename.empty() && (filename[0] == '/' || filename[0] == '.'))
    {
      //TRACE(filename);
      filenames.insert(filename);
    }
    else if (!filename.empty() && filename[0] != '/' && filename[0] != '.')
    {
      //Add full path
      const std::string s
        = GetPath(pro_file->GetQtCreatorProFilename());
      //  = boost::filesystem::path(pro_file->GetQtCreatorProFilename()).parent_path().string();
      assert(s.size() > 6);
      const std::string t = s + "/" + filename;
      //TRACE(t);
      filenames.insert(t);
    }
  }

  return filenames;
}

const About QtCreatorProFileZipScript::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "QtCreatorProFileZipScript",
    "class to create a zip file from a .pro file",
    "the 19th of May 2013",
    "2013",
    "http://www.richelbilderbeek.nl/CppQtCreatorProFileZipScript.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::vector<std::string> QtCreatorProFileZipScript::GetFilesInFolder(const std::string& folder)
{
  QDir dir(folder.c_str());
  dir.setFilter(QDir::Files);
  const QFileInfoList list = dir.entryInfoList();

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const int size = list.size();
  for (int i = 0; i != size; ++i)
  {
    const std::string file_name = list.at(i).fileName().toStdString();
    v.push_back(file_name);
  }
  return v;
}

const std::string QtCreatorProFileZipScript::GetPath(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

const std::vector<std::string> QtCreatorProFileZipScript::GetProFilesInFolder(const std::string& folder)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex for a correct Qt Creator project filename
  const boost::xpressive::sregex rex = boost::xpressive::sregex::compile(".*\\.(pro)\\>");

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  std::copy_if(v.begin(),v.end(),std::back_inserter(w),
    [rex](const std::string& s)
    {
      boost::xpressive::smatch what;
      return boost::xpressive::regex_match(s, what, rex);
    }
  );
  return w;
}

const std::string QtCreatorProFileZipScript::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtCreatorProFileZipScript::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-05-19: version 1.0: initial version");
  v.push_back("2013-08-19: version 1.1: replaced Boost.Regex by Boost.Xpressive");
  return v;
}

bool QtCreatorProFileZipScript::IsRegularFile(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

const boost::shared_ptr<QtCreatorProFileZipScript> QtCreatorProFileZipScript::Merge(
  const std::vector<boost::shared_ptr<const QtCreatorProFileZipScript> >& scripts)
{
  boost::shared_ptr<QtCreatorProFileZipScript> p;
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
void QtCreatorProFileZipScript::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtCreatorProFileZipScript::Test");
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
    if (!IsRegularFile(pro_file_name)) continue;

    assert(IsRegularFile(pro_file_name));
    const boost::shared_ptr<const QtCreatorProFile> pro_file(
      new QtCreatorProFile(pro_file_name) );
    assert(pro_file);

    const boost::shared_ptr<const QtCreatorProFileZipScript> zip_script(
      new QtCreatorProFileZipScript(pro_file) );
    assert(zip_script);

    const std::set<std::string> filenames = zip_script->GetFilenames();
    for (const std::string& filename: filenames)
    {
      if (!IsRegularFile(filename))
      {
        const std::string warning = "Warning: file \'" + filename + "\' not found";
        TRACE(warning);
        continue;
      }
      assert(IsRegularFile(filename));
    }
  }
  //GetProFiles
  {
    const std::size_t n = GetProFilesInFolder("").size();
    std::ofstream f("tmp23465278.pro");
    const std::size_t p = GetProFilesInFolder("").size();
    assert(n == p - 1);
    std::remove("tmp23465278.pro");
    const std::size_t q = GetProFilesInFolder("").size();
    assert(n == q);
  }
  TRACE("Finished QtCreatorProFileZipScript::Test successfully");
}
#endif

std::ostream& operator<<(std::ostream& os,const QtCreatorProFileZipScript& script)
{
  //using QtCreatorProFileZipScript::GetPath;
  assert(script.GetProFileName().size() > 6);
  assert(script.GetProFileName().substr(0,6) == std::string("../../"));

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
  const std::set<std::string,PathOrdering> file_names(
    script.GetFilenames().begin(),script.GetFilenames().end());

  std::set<std::string,PathOrdering> folder_names;
  //Add the folders added by the .pro file
  for (const std::string filename: file_names)
  {
    std::string s = QtCreatorProFileZipScript::GetPath(filename);
    //std::string s = boost::filesystem::path(filename).parent_path().string();
    while (!s.empty())
    {
      folder_names.insert(s);
      s = QtCreatorProFileZipScript::GetPath(s);
      //s = boost::filesystem::path(s).parent_path().string();
    }
  }


  for (const std::string& s: folder_names)
  {
    if (s.size() > 6 && s.substr(0,6) == std::string("../../"))
    {
      os << "mkdir Projects/" <<  s.substr(6,s.size() - 6) << '\n';
    }
  }

  os << '\n';
  os << "echo \"Copying files\"" << '\n';
  os << '\n';

  for (const std::string& s: file_names)
  {
    if (s.size() > 6 && s.substr(0,6) == std::string("../../"))
    {
      os << "cp " << s << " Projects/" + s.substr(6,s.size() - 6) << '\n';
    }
    else if (s.size() > 3 && s.substr(0,1) != std::string("."))
    {
      //A file in the .pro file its folder
      os << "cp " << s << " Projects/"
        //<< boost::filesystem::path(script.GetProFileName()).parent_path().string()
        << QtCreatorProFileZipScript::GetPath(script.GetProFileName())
        << s
        << '\n';
    }
  }

  os << '\n';
  os << "FILENAME=\""
     << QtCreatorProFileZipScript::GetPath( script.GetProFileName() )
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
      if (s.size() > 6 && s.substr(0,6) == std::string("../../"))
      {
         os << "rm Projects/" + s.substr(6,s.size() - 6) << "/*.*" << '\n';
      }
    }
  );

  os << "rm Projects/*.*" << '\n';

  std::for_each(folder_names.rbegin(),folder_names.rend(),
    [&os](const std::string& s)
    {
      if (s.size() > 6 && s.substr(0,6) == std::string("../../"))
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
      = QtCreatorProFileZipScript::GetAbout().CreateAboutText();
    std::transform(w.begin(),w.end(),
    std::ostream_iterator<std::string>(os,"\n"),
      [](const std::string& s)
      {
        return std::string("# ") + s;
      }
    );
  }
  return os;
}
