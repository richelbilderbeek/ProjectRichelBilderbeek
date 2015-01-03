//---------------------------------------------------------------------------
/*
FileIo, class with file I/O functions
Copyright (C) 2013-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppFileIo.htm
//---------------------------------------------------------------------------
#include "fileio.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>
#include <fstream>

#include <boost/xpressive/xpressive.hpp>

#include <QDir>
#include <QFile>

#include "filecopymode.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::fileio::FileIo::FileIo()
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::fileio::FileIo::ConvertPathToUnix(const std::string& path) const noexcept
{
  std::string s = path;
  std::replace(std::begin(s),std::end(s),'\\','/');
  assert(IsUnixPath(s));
  return s;
}

void ribi::fileio::FileIo::CopyFile(
  const std::string& fileNameFrom,
  const std::string& fileNameTo,
  const CopyMode copy_mode
) const
{
  assert(IsRegularFile(fileNameFrom) && "Cannot copy a non-existing file");
  if (copy_mode == CopyMode::prevent_overwrite && IsRegularFile(fileNameTo))
  {
    throw std::logic_error("Copying to an existing file is not allowed");
  }
  if (IsRegularFile(fileNameTo))
  {
    //DeleteFile ensures a correct deletion
    DeleteFile(fileNameTo);
  }
  std::ifstream in{fileNameFrom.c_str()};
  std::ofstream out{fileNameTo.c_str()};
  out << in.rdbuf();
  out.close();
  in.close();
}

void ribi::fileio::FileIo::CreateFolder(const std::string& folder) const
{
  #ifndef NDEBUG
  if(IsFolder(folder))
  {
    TRACE("ERROR");
    TRACE(folder);
  }
  #endif
  assert(!IsFolder(folder)
    && "Can only create folders that do not exist yet");
  const auto cmd = "mkdir " + folder;
  const auto error = std::system(cmd.c_str());
  #ifndef NDEBUG
  if (error) { TRACE(cmd); }
  #endif
  assert(!error && "Assume mkdir works under both Windows and Linux");
  if (error)
  {
    std::stringstream s;
    s << "ribi::fileio::FileIo::CreateFolder: "
      << "CreateFolder failed in creating the folder '" << folder << "': "
    ;
    TRACE(s.str());
    throw std::runtime_error(s.str());
  }
  assert(IsFolder(folder) && "it should work");
}

void ribi::fileio::FileIo::DeleteFile(const std::string& filename) const
{
  #ifndef NDEBUG
  if(!IsRegularFile(filename))
  {
    TRACE("ERROR");
    TRACE(filename);
  }
  #endif
  assert(IsRegularFile(filename)
    && "Can only delete existing files");
  std::remove(filename.c_str());

  //Under Windows, readonly files must be made deleteable
  if (IsRegularFile(filename))
  {
    #ifdef _WIN32
    const auto cmd = "attrib -r " + filename;
    std::system(cmd.c_str());
    std::remove(filename.c_str());
    #endif
  }

  #ifndef NDEBUG
  if (IsRegularFile(filename))
  {
    const auto s = "Failed to delete " + filename;
    TRACE(s);
  }
  #endif
  assert(!IsRegularFile(filename)
    && "File must not exist anymore");
}

void ribi::fileio::FileIo::DeleteFolder(const std::string& folder) const
{
  assert(IsFolder(folder)
    && "Can only delete folders that do exist");

  //Delete all files
  for (const auto& subfolder: GetFoldersInFolder(folder))
  {
    DeleteFolder(
      (folder.empty() ? folder : folder + GetPathSeperator())
      + subfolder
    );
  }
  assert(GetFoldersInFolder(folder).empty());
  for (const auto& filename: GetFilesInFolder(folder))
  {
    DeleteFile(
      (folder.empty() ? folder : folder + GetPathSeperator())
      + filename
   );
  }
  assert(GetFilesInFolder(folder).empty());
  const auto cmd = "rmdir " + folder;
  const auto error = std::system(cmd.c_str());
  assert(!error && "Assume rmdir works under both Windows and Linux");
  if (error)
  {
    std::stringstream s;
    s << "ribi::fileio::FileIo::DeleteFolder: "
      << "DeleteFolder failed in deleting the folder '" << folder << "': "
      << "failed by system call"
    ;
    TRACE(s.str());
    throw std::runtime_error(s.str());
  }
  if (IsFolder(folder))
  {
    std::stringstream s;
    s << "ribi::fileio::FileIo::DeleteFolder: "
      << "DeleteFolder failed in deleting the folder '" << folder << "'"
    ;
    TRACE(s.str());
    throw std::runtime_error(s.str());
  }
}

bool ribi::fileio::FileIo::FilesAreIdentical(
  const std::string& filename_a,
  const std::string& filename_b
) const
{
  #ifndef NDEBUG
  if (!IsRegularFile(filename_a))
  {
    TRACE(filename_a);
  }
  if (!IsRegularFile(filename_b))
  {
    TRACE(filename_b);
  }
  #endif
  assert(IsRegularFile(filename_a) && "File must exist to be compared");
  assert(IsRegularFile(filename_b) && "File must exist to be compared");
  const auto v = FileToVector(filename_a);
  const auto w = FileToVector(filename_b);
  return v == w;
}

std::string ribi::fileio::FileIo::FileToStr(
  const std::string& filename) const
{
  std::string s;
  for (const auto& t: FileToVector(filename))
  {
    s += t + '\n';
  }
  if (!s.empty()) s.pop_back();
  return s;
}

std::vector<std::string> ribi::fileio::FileIo::FileToVector(
  const std::string& filename) const
{
  #ifndef NDEBUG
  if (!IsRegularFile(filename))
  {
    TRACE(filename);
  }
  #endif
  assert(IsRegularFile(filename));
  assert(!IsFolder(filename));
  std::vector<std::string> v;
  std::ifstream in{filename.c_str()};
  assert(in.is_open());
  //Without this test in release mode,
  //the program might run indefinitely when the file does not exists
  if (!in.is_open())
  {
    const std::string s{"ERROR: file does not exist: " + filename};
    throw std::logic_error{s.c_str()};
  }
  for (int i=0; !in.eof(); ++i)
  {
    std::string s;
    std::getline(in,s);
    v.push_back(s); //Might throw std::bad_alloc
  }
  //Remove empty line at back of vector
  if (!v.empty() && v.back().empty()) v.pop_back();
  return v;
}

std::string ribi::fileio::FileIo::GetExtension(
  const std::string& filename) const noexcept
{
  return GetExtensionWithDot(filename);
}

std::string ribi::fileio::FileIo::GetExtensionNoDot(const std::string& filename) const noexcept
{
  static const boost::xpressive::sregex rex{
    boost::xpressive::sregex::compile("(.*)?(\\.)([A-Za-z]*)?" )
  };
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[3];
  }

  return "";
}

std::string ribi::fileio::FileIo::GetExtensionWithDot(const std::string& filename) const noexcept
{
  return
    ( std::count(filename.begin(),filename.end(),'.')
    ? "."
    : ""
    )
    + GetExtensionNoDot(filename);
}

std::string ribi::fileio::FileIo::GetFileBasename(const std::string& filename) const
{
  const boost::xpressive::sregex rex{
    boost::xpressive::sregex::compile("((.*)(/|\\\\))?([A-Za-z0-9_-]*)((\\.)([A-Za-z0-9]*))?" )
  };
  boost::xpressive::smatch what;

  if(boost::xpressive::regex_match( filename, what, rex ))
  {
    return what[4];
  }

  return "";
}

std::vector<std::string> ribi::fileio::FileIo::GetFilesInFolder(
  const std::string& folder) const
{
  assert(IsFolder(folder));
  QDir dir{folder.c_str()};
  dir.setFilter(QDir::Files);
  const QFileInfoList list{dir.entryInfoList()};

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const int size{list.size()};
  for (int i{0}; i != size; ++i)
  {
    const std::string file_name{list.at(i).fileName().toStdString()};
    v.push_back(file_name);
  }
  return v;
}

std::vector<std::string> ribi::fileio::FileIo::GetFilesInFolderRecursive(
  const std::string& root_folder) const
{
  assert(IsFolder(root_folder));

  //Files in root_folder
  std::vector<std::string> v;
  {
    const std::vector<std::string> files_here{
      GetFilesInFolder(root_folder)
    };
    //Copy the files and folders with path added
    std::transform(files_here.begin(),files_here.end(),std::back_inserter(v),
      [this,root_folder](const std::string& filename)
      {
        const std::string filename_here{
          root_folder + GetPathSeperator() + filename
        };
        assert(IsRegularFile(filename_here));
        return filename_here;
      }
    );
  }
  //Folders in root_folder
  std::vector<std::string> folders_todo;
  {
    const auto folders_here = GetFoldersInFolder(root_folder);
    std::transform(folders_here.begin(),folders_here.end(),std::back_inserter(folders_todo),
      [this,root_folder](const std::string& foldername)
      {
        const auto folder_here = root_folder + GetPathSeperator() + foldername;
        assert(IsFolder(folder_here));
        return folder_here;
      }
    );
  }

  //Search through all sub folders
  while (!folders_todo.empty())
  {
    const auto folder_todo =
      folders_todo.back(); //Read from the back, so push_back can be used

    //Done with this folder
    folders_todo.pop_back();

    #ifndef NDEBUG
    if(!(folders_todo.empty() || folders_todo.back() != folder_todo))
    {
      TRACE("ERROR");
      for (const auto& todo: folders_todo) { TRACE(todo); }
      for (const auto& result: v) { TRACE(result); }
    }
    #endif
    assert( (folders_todo.empty() || folders_todo.back() != folder_todo)
      && "Next folder must not be the one that is just processed");


    const auto files_here = GetFilesInFolder(folder_todo);
    const auto folders_here = GetFoldersInFolder(folder_todo);

    #ifndef NDEBUG
    for (const auto& folder_here: folders_here) { TRACE(folder_here); }
    #endif

    //Copy the files and folders with path added
    std::transform(files_here.begin(),files_here.end(),std::back_inserter(v),
      [this,folder_todo](const std::string& filename)
      {
        const std::string file_here {
          folder_todo + GetPathSeperator() + filename
        };
        assert(IsRegularFile(file_here));
        return file_here;
      }
    );
    std::transform(folders_here.begin(),folders_here.end(),std::back_inserter(folders_todo),
      [this,folder_todo](const std::string& foldername)
      {
        assert(!foldername.empty());
        const std::string subfolder_name {
          folder_todo + GetPathSeperator() + foldername
        };
        assert(subfolder_name != folder_todo);
        return subfolder_name;
      }
    );
  }
  return v;
}

std::vector<std::string> ribi::fileio::FileIo::GetFilesInFolderByRegex(
  const std::string& folder,
  const std::string& regex_str
) const
{
  #ifndef NDEBUG
  if(!IsFolder(folder))
  {
    TRACE("ERROR");
    TRACE(folder);
  }
  #endif

  //Get all filenames
  assert(IsFolder(folder));
  const auto v = GetFilesInFolder(folder);

  //Create the regex
  const auto rex = boost::xpressive::sregex::compile(regex_str);

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

std::vector<std::string> ribi::fileio::FileIo::GetFoldersInFolder(
  const std::string& folder) const
{
  assert(IsFolder(folder));
  QDir dir{folder.c_str()};
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot );
  //const QFileInfoList list{dir.entryInfoList()};
  const auto list = dir.entryInfoList();

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const auto size = list.size();
  for (auto i = 0; i != size; ++i)
  {
    const auto folder_name = list.at(i).fileName().toStdString();
    assert(!folder_name.empty());
    v.push_back(folder_name);
  }
  #ifndef NDEBUG
  for (const auto& s: v)
  {
    assert(std::count(v.begin(),v.end(),s) == 1
      && "Every folder name is unique");
  }
  #endif
  return v;
}

std::string ribi::fileio::FileIo::GetPath(const std::string& filename) const
{
  const auto a = filename.rfind("\\",filename.size());
  const auto b = filename.rfind("/",filename.size());
  std::size_t i{0};
  if (a != std::string::npos) { i = a; }
  if (b != std::string::npos) { i = std::max(i,b); }
  if (i >= filename.size())
  {
    TRACE("ERROR");
    TRACE(filename);
    TRACE(a);
    TRACE(b);
    TRACE(i);
    TRACE("BREAK");
  }
  //assert(i >= 0);
  assert(i < filename.size());
  return filename.substr(0,i);
}

std::string ribi::fileio::FileIo::GetPathSeperator() const noexcept
{
  #ifdef _WIN32
  return "\\";
  #else
  return "/";
  #endif
}

std::string ribi::fileio::FileIo::GetSuperFolder(const std::string& folder) const
{
  const auto a = folder.rfind("\\",folder.size());
  const auto b = folder.rfind("/",folder.size());
  std::size_t i{0};
  if (a != std::string::npos) { i = a; }
  if (b != std::string::npos) { i = std::max(i,b); }

  //assert(i >= 0);
  assert(i < folder.size());
  return
    i == 0
    ? ""
    : folder.substr(0,i);
}

std::string ribi::fileio::FileIo::GetTempFileName(const std::string& post) const
{
  //Limit the number of searches, to prevent the program from freezing
  //It might occur that the first random names are taken, because
  //of working without a randomize timer first
  for (auto i = 0; i!=1000; ++i)
  {
    std::stringstream s;
    s << "tmpfilename"
      << std::rand()
      << std::rand()
      << std::rand()
      << std::rand()
      << post;
    if (!IsRegularFile(s.str())) return s.str();
  }

  std::stringstream s;
  s << "ribi::fileio::FileIo::GetTempFileName: "
    << "Could not find a temporary file name"
  ;
  TRACE(s.str());
  throw std::runtime_error(s.str());
}

std::string ribi::fileio::FileIo::GetTempFileNameSimple(const std::string& post) const
{
  //Limit the number of searches, to prevent the program from freezing
  for (auto i = 0; i!=1000; ++i)
  {
    std::stringstream s;
    s << "tmp"
      << i
      << post;
    if (!IsRegularFile(s.str())) return s.str();
  }

  std::stringstream s;
  s << "ribi::fileio::FileIo::GetTempFileNameSimple: "
    << "Could not find a temporary file name"
  ;
  TRACE(s.str());
  throw std::runtime_error(s.str());
}


std::string ribi::fileio::FileIo::GetTempFolderName() const
{
  //Limit the number of searches, to prevent the program from freezing
  //It might occur that the first random names are taken, because
  //of working without a randomize timer first
  for (auto i = 0; i!=1000; ++i)
  {
    std::stringstream s;
    s << "tmpfoldername"
      << std::rand()
      << std::rand()
      << std::rand()
      << std::rand();
    if (!IsFolder(s.str())) return s.str();
  }

  std::stringstream s;
  s << "ribi::fileio::FileIo::GetTempFolderName: "
    << "Could not find a temporary folder name"
  ;
  TRACE(s.str());
  throw std::runtime_error(s.str());
}

std::string ribi::fileio::FileIo::GetVersion() noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::fileio::FileIo::GetVersionHistory() noexcept
{
  return {
    "2013-10-14: Version 1.0: initial version, used free functions only",
    "2013-11-08: Version 1.1: improved FileToVector, improved GetFileBasename, added some functions",
    "2013-12-10: Version 1.2: improved existing function, added some functions",
    "2014-03-24: Version 1.3: put free functions in FileIo class",
    "2014-07-15: Version 1.4: increased use of auto and initializer lists"
  };
}

bool ribi::fileio::FileIo::HasRightPathSeperators(const std::string& path) const noexcept
{
  #ifdef _WIN32
  const auto wrong = '/';
  #else
  const auto wrong = '\\';
  #endif
  return path.find(wrong) == std::string::npos;
}

bool ribi::fileio::FileIo::HasTwoPathSeperators(const std::string& path) const noexcept
{
  return path.find('/') != std::string::npos
    && path.find('\\') != std::string::npos;
}

bool ribi::fileio::FileIo::IsFolder(const std::string& filename) const noexcept
{
  return QDir(filename.c_str()).exists();
}

bool ribi::fileio::FileIo::IsRegularFile(const std::string& filename) const noexcept
{
  return !QDir(filename.c_str()).exists() && QFile::exists(filename.c_str());
}

bool ribi::fileio::FileIo::IsUnixPath(const std::string& path) const noexcept
{
  if (path.find('\\') != std::string::npos)
  {
    return false;
  }
  return true;
}

std::string ribi::fileio::FileIo::RemovePath(const std::string& filename) const
{
  std::vector<std::size_t> v;
  const auto a = filename.rfind("\\",filename.size());
  if (a != std::string::npos) v.push_back(a);
  const auto b = filename.rfind("/",filename.size());
  if (b != std::string::npos) v.push_back(b);
  if (v.empty()) return filename;
  const auto i = *std::max_element(std::begin(v),std::end(v));
  assert(i < filename.size());
  const auto j = i + 1;
  assert(j < filename.size());
  const auto s = filename.substr(j,filename.size() - j);
  return s;
}

void ribi::fileio::FileIo::RenameFile(
  const std::string& from,
  const std::string& to,
  const RenameMode rename_mode) const
{
  #ifndef NDEBUG
  if (!IsRegularFile(from))
  {
    TRACE(from);
  }
  #endif
  assert(IsRegularFile(from) && "Cannot rename a non-existing file");
  assert(from != to && "Cannot rename to the same filename");
  if (rename_mode == RenameMode::prevent_overwrite && IsRegularFile(to))
  {
    throw std::logic_error("Renaming to an existing file is not allowed");
  }
  if (IsRegularFile(to))
  {
    //DeleteFile ensures a correct deletion
    DeleteFile(to);
  }
  const int result{std::rename(from.c_str(),to.c_str())};
  if (result == 0)
  {
    assert( IsRegularFile(to)  );
    assert(!IsRegularFile(from));
  }
  else
  {
    //Delete 'from' manually
    assert( IsRegularFile(to)  );
    DeleteFile(from);
    assert( IsRegularFile(to));
    assert(!IsRegularFile(from));
  }
}

std::string ribi::fileio::FileIo::SimplifyPath(const std::string& s) const noexcept
{
  std::string t{s};
  //UNIX
  while (1)
  {
    static const boost::xpressive::sregex regex{boost::xpressive::sregex::compile(R"((/\w*/\.\./))")};

    const std::string new_t{boost::xpressive::regex_replace(
      t,regex,"/")
    };
    if (t == new_t) break;
    t = new_t;
  }
  //Win32
  while (1)
  {
    static const boost::xpressive::sregex regex{boost::xpressive::sregex::compile(R"((\\\w*\\\.\.\\))")};

    const std::string new_t{
      boost::xpressive::regex_replace(t,regex,"\\")
    };
    if (t == new_t) break;
    t = new_t;
  }
  //UNIX
  while (1)
  {
    static const boost::xpressive::sregex regex{boost::xpressive::sregex::compile(R"((^\w*/\.\.))")};

    const std::string new_t{
      boost::xpressive::regex_replace(t,regex,"")};
    if (t == new_t) break;
    t = new_t;
  }
  //Win32
  while (1)
  {
    static const boost::xpressive::sregex regex = boost::xpressive::sregex::compile(R"((^\w*\\\.\.))");

    const std::string new_t = boost::xpressive::regex_replace(
      t,
      regex,
      ""
    );
    if (t == new_t) break;
    t = new_t;
  }

  #ifdef UDNEFINFE467830786530475
  while (1)
  {
    static const boost::xpressive::sregex regex = boost::xpressive::sregex::compile("((/|_b)\\w*/..(/|_b))");

    //const std::string new_t = boost::regex_replace(t,boost::regex("/\\w*/../"),"/");
    const std::string new_t = boost::xpressive::regex_replace(
      t,
      regex,
      ""
    );
    if (t == new_t) break;
    t = new_t;
  }
  #endif
  return t;
}


#ifndef NDEBUG
void ribi::fileio::FileIo::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //CopyFile
  for (int i=0; i!=2; ++i)
  {
    const std::string filename { GetTempFileName() };
    const std::string filename_copy { GetTempFileName() };

    //Create a regular file
    assert(!IsRegularFile(filename));
    assert(!IsRegularFile(filename_copy));
    {
      std::ofstream f;
      f.open(filename.c_str());
      f << "TEMP TEXT";
      f.close();
    }
    assert(IsRegularFile(filename));
    assert(!IsRegularFile(filename_copy));

    const CopyMode copy_mode {
      i == 0
      ? CopyMode::allow_overwrite
      : CopyMode::prevent_overwrite
    };
    CopyFile(filename,filename_copy,copy_mode);

    assert(IsRegularFile(filename));
    assert(IsRegularFile(filename_copy));

    DeleteFile(filename);
    DeleteFile(filename_copy);
    assert(!IsRegularFile(filename) && "Temporary file must be cleaned up");
    assert(!IsRegularFile(filename_copy) && "Temporary file must be cleaned up");
  }
  //FilesAreIdentical
  {
    const std::vector<std::string> filenames { GetTempFileName(), GetTempFileName(), GetTempFileName() };
    const int n_filenames = filenames.size();
    for (const std::string& filename: filenames)
    {
      std::ofstream f(filename.c_str());
      f << filename;
    }

    for (int i=0; i!=n_filenames; ++i)
    {
      const std::string s = filenames[i];
      for (int j=0; j!=n_filenames; ++j)
      {
        const std::string t = filenames[j];
        assert(FilesAreIdentical(s,t) == (i == j));
      }
    }
    for (const std::string& filename: filenames)
    {
      DeleteFile(filename);
      assert(!IsRegularFile(filename) && "Temporary file must be cleaned up");
    }
  }
  //FileToVector and VectorToFile, indidual
  {
    const std::string filename = GetTempFileName();
    assert(!IsRegularFile(filename));
    const std::vector<std::string> v { "A","BC", "DEF" };
    VectorToFile(v,filename);
    assert(IsRegularFile(filename));
    const std::vector<std::string> w { FileToVector(filename) };
    if (v != w)
    {
      TRACE(v.size());
      for (const std::string& s: v) TRACE(s);
      TRACE(w.size());
      for (const std::string& t: w) TRACE(t);
    }
    assert(v == w);
    DeleteFile(filename);
    assert(!IsRegularFile(filename));
  }
  //FileToVector and VectorToFile, many
  {
    std::vector<std::vector<std::string>> v
    {
      { },
      { "A" },
      { "A", "B" },
      { "A", "B", "C" },
      { "A", "", "C" }
    };
    for (const std::vector<std::string>& w: v)
    {
      const std::string filename = GetTempFileName();
      assert(!IsRegularFile(filename));
      VectorToFile(w,filename);
      assert(IsRegularFile(filename));
      const std::vector<std::string> x { FileToVector(filename) };
      if (w != x)
      {
        TRACE(w.size());
        for (const std::string& s: w) TRACE(s);
        TRACE(x.size());
        for (const std::string& t: x) TRACE(t);
      }
      assert(w == x);
      DeleteFile(filename);
      assert(!IsRegularFile(filename));
    }
  }
  //GetTempFolderName, CreateFolder and DeleteFolder
  {
    //Depth 1
    {
      const std::string f { GetTempFolderName() };
      assert(!IsFolder(f) && "A temporary folder name must not exist");
      CreateFolder(f);
      assert(IsFolder(f));
      DeleteFolder(f);
      assert(!IsFolder(f) && "Temporary folder must be cleaned up");
    }
    //Depth 2
    {
      const std::string super_folder { GetTempFolderName() };
      assert(!IsFolder(super_folder) && "A temporary folder name must not exist");
      CreateFolder(super_folder);
      assert(IsFolder(super_folder));
      {
        const std::string f { GetTempFolderName() };
        assert(!IsFolder(f) && "A temporary folder name must not exist");
        CreateFolder(f);
        assert(IsFolder(f));
        DeleteFolder(f);
        assert(!IsFolder(f));
      }
      assert(IsFolder(super_folder));
      DeleteFolder(super_folder);
      assert(!IsFolder(super_folder) && "Temporary folder must be cleaned up");
    }
  }
  //GetFileBasename
  {
    assert(GetFileBasename("") == "");
    assert(GetFileBasename("tmp") == "tmp");
    assert(GetFileBasename("tmp.") == "tmp");
    assert(GetFileBasename("tmp.x") == "tmp");
    assert(GetFileBasename("tmp.txt") == "tmp");
    assert(GetFileBasename("tmp.text") == "tmp");
    assert(GetFileBasename("tmp.longextension") == "tmp");
    assert(GetFileBasename("input_triangle.txt") == "input_triangle");
    assert(GetFileBasename("tmp") == "tmp");
    assert(GetFileBasename("MyFolder/tmp") == "tmp");
    assert(GetFileBasename("MyFolder/tmp.txt") == "tmp");
    assert(GetFileBasename("MyFolder\\tmp.txt") == "tmp");
    assert(GetFileBasename("MyFolder/MyFolder/tmp") == "tmp");
    assert(GetFileBasename("MyFolder/MyFolder/tmp.txt") == "tmp");
    assert(GetFileBasename("MyFolder/MyFolder\\tmp.txt") == "tmp");
    assert(GetFileBasename("MyFolder/My-Folder\\tmp.txt") == "tmp");
    assert(GetFileBasename("MyFolder/My_Folder\\tmp.txt") == "tmp");
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameConnectThree")
      == "GameConnectThree");
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameAminoAcidFighter")
      == "GameAminoAcidFighter");
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameK3OpEenRij")
      == "GameK3OpEenRij");
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Projects/ProjectRichelBilderbeek")
      == "ProjectRichelBilderbeek");
  }
  //GetExtension
  {
    assert(GetExtensionNoDot("") == "");
    assert(GetExtensionNoDot("tmp") == "");
    assert(GetExtensionNoDot("tmp.") == "");
    assert(GetExtensionNoDot("tmp.x") == "x");
    assert(GetExtensionNoDot("tmp.txt") == "txt");
    assert(GetExtensionNoDot("tmp.text") == "text");
    assert(GetExtensionNoDot("tmp.longextension") == "longextension");
    assert(GetExtensionNoDot("input_triangle.txt") == "txt");
    assert(GetExtensionNoDot("tmp") == "");
    assert(GetExtensionNoDot("MyFolder/tmp") == "");
    assert(GetExtensionNoDot("MyFolder/tmp.txt") == "txt");
    assert(GetExtensionNoDot("MyFolder\\tmp.txt") == "txt");
    assert(GetExtensionNoDot("MyFolder/MyFolder/tmp") == "");
    assert(GetExtensionNoDot("MyFolder/MyFolder/tmp.txt") == "txt");
    assert(GetExtensionNoDot("MyFolder/MyFolder\\tmp.txt") == "txt");
    assert(GetExtensionNoDot("MyFolder/My-Folder\\tmp.txt") == "txt");
    assert(GetExtensionNoDot("MyFolder/My_Folder\\tmp.txt") == "txt");

    assert(GetExtensionWithDot("") == "");
    assert(GetExtensionWithDot("tmp") == "");
    assert(GetExtensionWithDot("tmp.") == ".");
    assert(GetExtensionWithDot("tmp.x") == ".x");
    assert(GetExtensionWithDot("tmp.txt") == ".txt");
    assert(GetExtensionWithDot("tmp.text") == ".text");
    assert(GetExtensionWithDot("tmp.longextension") == ".longextension");
    assert(GetExtensionWithDot("input_triangle.txt") == ".txt");
    assert(GetExtensionWithDot("tmp") == "");
    assert(GetExtensionWithDot("MyFolder/tmp") == "");
    assert(GetExtensionWithDot("MyFolder/tmp.txt") == ".txt");
    assert(GetExtensionWithDot("MyFolder\\tmp.txt") == ".txt");
    assert(GetExtensionWithDot("MyFolder/MyFolder/tmp") == "");
    assert(GetExtensionWithDot("MyFolder/MyFolder/tmp.txt") == ".txt");
    assert(GetExtensionWithDot("MyFolder/MyFolder\\tmp.txt") == ".txt");
    assert(GetExtensionWithDot("MyFolder/My-Folder/tmp.txt") == ".txt");
    assert(GetExtensionWithDot("MyFolder/My_Folder\\tmp.txt") == ".txt");

    assert(GetExtension("") == "");
    assert(GetExtension("tmp") == "");
    assert(GetExtension("tmp.") == ".");
    assert(GetExtension("tmp.x") == ".x");
    assert(GetExtension("tmp.txt") == ".txt");
    assert(GetExtension("tmp.text") == ".text");
    assert(GetExtension("tmp.longextension") == ".longextension");
    assert(GetExtension("input_triangle.txt") == ".txt");
    assert(GetExtension("tmp") == "");
    assert(GetExtension("MyFolder/tmp") == "");
    assert(GetExtension("MyFolder/tmp.txt") == ".txt");
    assert(GetExtension("MyFolder\\tmp.txt") == ".txt");
    assert(GetExtension("MyFolder/MyFolder/tmp") == "");
    assert(GetExtension("MyFolder/MyFolder/tmp.txt") == ".txt");
    assert(GetExtension("MyFolder/MyFolder\\tmp.txt") == ".txt");
    assert(GetExtension("MyFolder/My_Folder/tmp.txt") == ".txt");
    assert(GetExtension("MyFolder/My-Folder\\tmp.txt") == ".txt");
  }
  //GetFilesInFolderRecursive
  {
    //Use the following structure:
    // - local.txt
    // - my_folder1/in_folder1.txt
    // - my_folder1/in_folder2.txt
    // - my_folder2/in_folder1.txt
    // - my_folder2/in_folder2.txt
    // - my_folder/my_subfolder/in_subfolder.txt
    const std::string local_filename { "local.txt" };
    const std::string folder_name1 { "my_folder1" };
    const std::string folder_name2 { "my_folder2" };
    const std::string in_folder_filename1 { "in_folder.txt1" };
    const std::string in_folder_filename2 { "in_folder.txt2" };
    const std::string subfolder_name1 { "my_subfolder1" };
    const std::string subfolder_name2 { "my_subfolder2" };
    const std::string in_subfolder_filename1 { "in_subfolder1.txt" };
    const std::string in_subfolder_filename2 { "in_subfolder2.txt" };
    //Folder creation
    for (const std::string folder_name:
      {
        folder_name1,
        folder_name1 + GetPathSeperator() + subfolder_name1,
        folder_name1 + GetPathSeperator() + subfolder_name2,
        folder_name2,
        folder_name2 + GetPathSeperator() + subfolder_name1,
        folder_name2 + GetPathSeperator() + subfolder_name2,
      }
    )
    {
      if (!IsFolder(folder_name))
      {
        const std::string cmd = "mkdir " + folder_name;
        const int error = std::system(cmd.c_str());
        assert(!error);
      }
      assert(IsFolder(folder_name));
    }
    //File creation
    for (const std::string filename:
      {
        local_filename,
        folder_name1 + GetPathSeperator() + in_folder_filename1,
        folder_name1 + GetPathSeperator() + in_folder_filename2,
        folder_name2 + GetPathSeperator() + in_folder_filename1,
        folder_name2 + GetPathSeperator() + in_folder_filename2,
        folder_name1 + GetPathSeperator() + subfolder_name1 + GetPathSeperator() + in_subfolder_filename1,
        folder_name1 + GetPathSeperator() + subfolder_name1 + GetPathSeperator() + in_subfolder_filename2,
        folder_name1 + GetPathSeperator() + subfolder_name2 + GetPathSeperator() + in_subfolder_filename1,
        folder_name1 + GetPathSeperator() + subfolder_name2 + GetPathSeperator() + in_subfolder_filename2,
        folder_name2 + GetPathSeperator() + subfolder_name1 + GetPathSeperator() + in_subfolder_filename1,
        folder_name2 + GetPathSeperator() + subfolder_name1 + GetPathSeperator() + in_subfolder_filename2,
        folder_name2 + GetPathSeperator() + subfolder_name2 + GetPathSeperator() + in_subfolder_filename1,
        folder_name2 + GetPathSeperator() + subfolder_name2 + GetPathSeperator() + in_subfolder_filename2,
      }
    )
    {
      if (!IsRegularFile(filename))
      {
        std::ofstream f(filename.c_str());
      }
      assert(IsRegularFile(filename));
    }

    //Reading of the files and folders created
    const std::vector<std::string> v {
      GetFilesInFolderRecursive(folder_name1)
    };
    assert(v.size() == 6);

    //Clean up
    DeleteFolder(folder_name1);
    DeleteFolder(folder_name2);
    assert(!IsFolder(folder_name1) && "Temporary folder must be cleaned up");
    assert(!IsFolder(folder_name2) && "Temporary folder must be cleaned up");
  }
  //GetPath
  {
    assert(GetPath("/anypath/anyfile.cpp")=="/anypath");
    assert(GetPath("/any-path/any-file.cpp")=="/any-path");
    assert(GetPath("/any-path/any_file.cpp")=="/any-path");
    assert(GetPath("/any_path/any-file.cpp")=="/any_path");
    assert(GetPath("/any_path/any_file.cpp")=="/any_path");
    assert(GetPath("C:\\any-path\\any-file.cpp")=="C:\\any-path");
    assert(GetPath("C:\\any-path\\any_file.cpp")=="C:\\any-path");
    assert(GetPath("C:\\any-path\\anyfile.cpp")=="C:\\any-path");
    assert(GetPath("C:\\any_path\\any-file.cpp")=="C:\\any_path");
    assert(GetPath("C:\\any_path\\any_file.cpp")=="C:\\any_path");
    assert(GetPath("C:\\any_path\\anyfile.cpp")=="C:\\any_path");
    assert(GetPath("C:\\anypath\\anyfile.cpp")=="C:\\anypath");

  }
  //GetSuperFolder
  {
    assert(GetSuperFolder("C:\\A\\B")=="C:\\A");
    assert(GetSuperFolder("C:\\A\\B\\C")=="C:\\A\\B");
    assert(GetSuperFolder("C:\\")=="C:");
    assert(GetSuperFolder("C:")=="");
    assert(GetSuperFolder("/A/B")=="/A");
    assert(GetSuperFolder("/A/B/C")=="/A/B");
    assert(GetSuperFolder("/A")=="");
    assert(GetSuperFolder("C:\\AnySuperFolder\\AnyFolder")=="C:\\AnySuperFolder");
    assert(GetSuperFolder("C:\\AnySuperFolder\\Any_Folder")=="C:\\AnySuperFolder");
    assert(GetSuperFolder("C:\\AnySuperFolder\\Any-Folder")=="C:\\AnySuperFolder");
    assert(GetSuperFolder("C:\\Any_Super_Folder\\Any_Folder")=="C:\\Any_Super_Folder");
    assert(GetSuperFolder("C:\\Any_Super_Folder\\Any-Folder")=="C:\\Any_Super_Folder");
    assert(GetSuperFolder("C:\\Any-Super-Folder\\Any_Folder")=="C:\\Any-Super-Folder");
    assert(GetSuperFolder("C:\\Any-Super-Folder\\Any-Folder")=="C:\\Any-Super-Folder");
    assert(GetSuperFolder("/AnySuperFolder/AnyFolder")=="/AnySuperFolder");
    assert(GetSuperFolder("/AnySuperFolder/Any_Folder")=="/AnySuperFolder");
    assert(GetSuperFolder("/AnySuperFolder/Any-Folder")=="/AnySuperFolder");
    assert(GetSuperFolder("/Any_Super_Folder/Any_Folder")=="/Any_Super_Folder");
    assert(GetSuperFolder("/Any_Super_Folder/Any-Folder")=="/Any_Super_Folder");
    assert(GetSuperFolder("/Any-Super-Folder/Any_Folder")=="/Any-Super-Folder");
    assert(GetSuperFolder("/Any-Super-Folder/Any-Folder")=="/Any-Super-Folder");
  }
  //IsRegularFile
  {
    {
      const std::string filename { GetTempFileName() };

      //Create a regular file
      assert(!IsRegularFile(filename));
      {
        std::fstream f;
        f.open(filename.c_str(),std::ios::out);
        f << "TEMP TEXT";
        f.close();
      }
      assert(IsRegularFile(filename));

      DeleteFile(filename);

      assert(!IsRegularFile(filename) && "Temporary file must be cleaned up");
    }
  }
  //RemovePath
  {
    assert(RemovePath("x.txt") == "x.txt");
    assert(RemovePath("MyFolder/x.txt") == "x.txt");
    assert(RemovePath("Another/MyFolder/x.txt") == "x.txt");
    assert(RemovePath("Yet/Another/MyFolder/x.txt") == "x.txt");
    assert(RemovePath("MyFolder\\x.txt") == "x.txt");
    assert(RemovePath("Another\\MyFolder\\x.txt") == "x.txt");
    assert(RemovePath("Yet\\Another\\MyFolder\\x.txt") == "x.txt");
    assert(RemovePath("Another/MyFolder\\x.txt") == "x.txt");
    assert(RemovePath("Another\\MyFolder/x.txt") == "x.txt");
    assert(RemovePath("Yet\\Another/MyFolder\\x.txt") == "x.txt");
    assert(RemovePath("Yet\\Another\\MyFolder/x.txt") == "x.txt");
    assert(RemovePath("Yet\\An-other\\MyFolder/x.txt") == "x.txt");
    assert(RemovePath("Yet\\An_other\\MyFolder/x.txt") == "x.txt");
    assert(RemovePath("Yet\\Another\\MyFolder/x_y.txt") == "x_y.txt");
    assert(RemovePath("Yet\\Another\\MyFolder/x-y.txt") == "x-y.txt");
  }
  //RenameFile
  {
    const std::string filename_from { GetTempFileName() };
    const std::string filename_to   { GetTempFileName() };

    assert(!IsRegularFile(filename_from));
    assert(!IsRegularFile(filename_to));

    //Create new file
    {
      std::ofstream f(filename_from.c_str());
      f << "TMP";
      f.close();
    }

    //Only filename_from will exist
    assert( IsRegularFile(filename_from));
    assert(!IsRegularFile(filename_to));

    //Rename
    RenameFile(filename_from,filename_to);

    //Only filename_to will exist
    assert(!IsRegularFile(filename_from));
    assert( IsRegularFile(filename_to));

    //Clean up
    DeleteFile(filename_to);
    assert(!IsRegularFile(filename_to) && "Temporary file must be cleaned up");
  }
  //SimplifyPath
  {
    assert(SimplifyPath("/home/richel/Projects/Tools/ToolTestProFile/../../Classes/CppQtAboutDialog/qtaboutdialog.ui")
      == "/home/richel/Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui");
    assert(SimplifyPath("\\home\\richel\\Projects\\Tools\\ToolTestProFile\\..\\..\\Classes\\CppQtAboutDialog\\qtaboutdialog.ui")
      == "\\home\\richel\\Projects\\Classes\\CppQtAboutDialog\\qtaboutdialog.ui");
    assert(SimplifyPath("/home/richel/Projects/Tools/../Classes/CppQtAboutDialog/qtaboutdialog.ui")
      == "/home/richel/Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui");
    assert(SimplifyPath("\\home\\richel\\Projects\\Tools\\..\\Classes\\CppQtAboutDialog\\qtaboutdialog.ui")
      == "\\home\\richel\\Projects\\Classes\\CppQtAboutDialog\\qtaboutdialog.ui");
    assert(SimplifyPath("/home/richel/Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui")
      == "/home/richel/Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui");
    assert(SimplifyPath("\\home\\richel\\Projects\\Classes\\CppQtAboutDialog\\qtaboutdialog.ui")
      == "\\home\\richel\\Projects\\Classes\\CppQtAboutDialog\\qtaboutdialog.ui");
    assert(SimplifyPath("Tools/..") == "");
    assert(SimplifyPath("Tools\\..") == "");
    assert(SimplifyPath("Tools/../A") == "/A");
    assert(SimplifyPath("Tools\\..\\A") == "\\A");
    assert(SimplifyPath("Tools/../A/B") == "/A/B");
    assert(SimplifyPath("Tools\\..\\A\\B") == "\\A\\B");
    assert(SimplifyPath("../../Tools/ToolCreateQtProjectZipFile/../../Libraries/Boost.pri")
      == "../../Libraries/Boost.pri");
    assert(SimplifyPath("..\\..\\Tools\\ToolCreateQtProjectZipFile\\..\\..\\Libraries\\Boost.pri")
      == "..\\..\\Libraries\\Boost.pri");
  }
  //HasRightPathSeperators
  {
    #ifdef _WIN32
    assert( HasRightPathSeperators("\\A\\B\\text.txt"));
    assert(!HasRightPathSeperators("/A/B/text.txt"));
    #else
    assert(!HasRightPathSeperators("\\A\\B\\text.txt"));
    assert( HasRightPathSeperators("/A/B/text.txt"));
    #endif
  }
  //HasTwoPathSeperators
  {
    assert(!HasTwoPathSeperators("\\A\\B\\text.txt"));
    assert(!HasTwoPathSeperators("/A/B/text.txt"));

    assert( HasTwoPathSeperators("/A\\B/text.txt"));
    assert( HasTwoPathSeperators("\\A/B/text.txt"));
    assert( HasTwoPathSeperators("/A/B\\text.txt"));
    assert( HasTwoPathSeperators("/A\\B\\text.txt"));
    assert( HasTwoPathSeperators("\\A\\B/text.txt"));
    assert( HasTwoPathSeperators("\\A/B\\text.txt"));
  }
  //IsUnixPath
  {
    assert(!IsUnixPath("\\A\\B\\text.txt"));
    assert( IsUnixPath("/A/B/text.txt"));
    assert(!IsUnixPath("/A\\B/text.txt"));
    assert(!IsUnixPath("\\A/B/text.txt"));
    assert(!IsUnixPath("/A/B\\text.txt"));
    assert(!IsUnixPath("/A\\B\\text.txt"));
    assert(!IsUnixPath("\\A\\B/text.txt"));
    assert(!IsUnixPath("\\A/B\\text.txt"));
  }
  //ConvertPathToUnix
  {
    assert(IsUnixPath(ConvertPathToUnix("\\A\\B\\text.txt")));
    assert(IsUnixPath(ConvertPathToUnix("/A/B/text.txt")));
    assert(IsUnixPath(ConvertPathToUnix("/A\\B/text.txt")));
    assert(IsUnixPath(ConvertPathToUnix("\\A/B/text.txt")));
    assert(IsUnixPath(ConvertPathToUnix("/A/B\\text.txt")));
    assert(IsUnixPath(ConvertPathToUnix("/A\\B\\text.txt")));
    assert(IsUnixPath(ConvertPathToUnix("\\A\\B/text.txt")));
    assert(IsUnixPath(ConvertPathToUnix("\\A/B\\text.txt")));
  }
}
#endif

void ribi::fileio::FileIo::VectorToFile(
  const std::vector<std::string>& v,
  const std::string& filename,
  const CopyMode copy_mode
) const
{
  if (copy_mode == CopyMode::prevent_overwrite)
  {
    assert(!IsRegularFile(filename) && "File must not exist");
    if (IsRegularFile(filename))
    {
      std::stringstream s;
      s
        << "VectorToFile: not allowed to overwrite file '"
        << filename
        << "'";
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
  }
  {
    std::ofstream f(filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  assert(IsRegularFile(filename));
}
