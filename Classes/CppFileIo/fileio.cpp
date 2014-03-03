#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "fileio.h"

#include <cassert>
#include <fstream>

#include <boost/xpressive/xpressive.hpp>

#include <QDir>
#include <QFile>

#include "filecopymode.h"
#include "trace.h"
#pragma GCC diagnostic pop


void ribi::fileio::CopyFile(
  const std::string& fileNameFrom,
  const std::string& fileNameTo,
  const CopyMode copy_mode)
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
  std::ifstream in (fileNameFrom.c_str());
  std::ofstream out(fileNameTo.c_str());
  out << in.rdbuf();
  out.close();
  in.close();
}

void ribi::fileio::CreateFolder(const std::string& folder)
{
  #ifndef NDEBUG
  if(IsFolder(folder))
  {
    TRACE("ERROR");
    TRACE(folder);
  }
  #endif
  assert(!IsFolder(folder)
    && "Can only create folders that do not exist yes");
  const std::string cmd = "mkdir " + folder;
  const int error = std::system(cmd.c_str());
  #ifndef NDEBUG
  if (error) { TRACE(cmd); }
  #endif
  assert(!error && "Assume mkdir works under both Windows and Linux");
  if (error) throw std::runtime_error("CreateFolder failed");
  assert(IsFolder(folder) && "it should work");
}

void ribi::fileio::DeleteFile(const std::string& filename)
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
    const std::string cmd = "attrib -r " + filename;
    std::system(cmd.c_str());
    std::remove(filename.c_str());
    #endif
  }

  #ifndef NDEBUG
  if (IsRegularFile(filename))
  {
    const std::string s = "Failed to delete " + filename;
    TRACE(s);
  }
  #endif
  assert(!IsRegularFile(filename)
    && "File must not exist anymore");
}

void ribi::fileio::DeleteFolder(const std::string& folder)
{
  assert(IsFolder(folder)
    && "Can only delete folders that do exist");

  //Delete all files
  for (const std::string& subfolder: GetFoldersInFolder(folder))
  {
    DeleteFolder(
      (folder.empty() ? folder : folder + fileio::GetPathSeperator())
      + subfolder
    );
  }
  assert(GetFoldersInFolder(folder).empty());
  for (const std::string& filename: GetFilesInFolder(folder))
  {
    DeleteFile(
      (folder.empty() ? folder : folder + fileio::GetPathSeperator())
      + filename
   );
  }
  assert(GetFilesInFolder(folder).empty());
  const std::string cmd = "rmdir " + folder;
  const int error = std::system(cmd.c_str());
  assert(!error && "Assume rmdir works under both Windows and Linux");
  if (error)
  {
    TRACE(folder);
    throw std::runtime_error("DeleteFolder failed by system call");
  }
  if (IsFolder(folder))
  {
    TRACE(folder);
    throw std::runtime_error("DeleteFolder failed in deleting the folder");
  }
}

bool ribi::fileio::FilesAreIdentical(
  const std::string& filename_a,
  const std::string& filename_b)
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
  const std::vector<std::string> v { FileToVector(filename_a) };
  const std::vector<std::string> w { FileToVector(filename_b) };
  return v == w;
}

std::vector<std::string> ribi::fileio::FileToVector(const std::string& filename)
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
  std::ifstream in(filename.c_str());
  assert(in.is_open());
  //Without this test in release mode,
  //the program might run indefinitely when the file does not exists
  if (!in.is_open())
  {
    const std::string s = "ERROR: file does not exist: " + filename;
    throw std::logic_error(s.c_str());
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

std::string ribi::fileio::GetExtension(const std::string& filename) noexcept
{
  return GetExtensionWithDot(filename);
}

std::string ribi::fileio::GetExtensionNoDot(const std::string& filename) noexcept
{
  static const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "(.*)?(\\.)([A-Za-z]*)?" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[3];
  }

  return "";
}

std::string ribi::fileio::GetExtensionWithDot(const std::string& filename) noexcept
{
  return
    ( std::count(filename.begin(),filename.end(),'.')
    ? std::string(".")
    : std::string("")
    )
    + GetExtensionNoDot(filename);
}

std::string ribi::fileio::GetFileBasename(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "((.*)(/|\\\\))?([A-Za-z0-9_-]*)((\\.)([A-Za-z0-9]*))?" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[4];
  }

  return "";
}

std::vector<std::string> ribi::fileio::GetFilesInFolder(const std::string& folder)
{
  assert(IsFolder(folder));
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

std::vector<std::string> ribi::fileio::GetFilesInFolderRecursive(const std::string& root_folder)
{
  assert(IsFolder(root_folder));

  //Files in root_folder
  std::vector<std::string> v;
  {
    const std::vector<std::string> files_here {
      GetFilesInFolder(root_folder)
    };
    //Copy the files and folders with path added
    std::transform(files_here.begin(),files_here.end(),std::back_inserter(v),
      [root_folder](const std::string& filename)
      {
        const std::string filename_here {
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
    const std::vector<std::string> folders_here {
      GetFoldersInFolder(root_folder)
    };
    std::transform(folders_here.begin(),folders_here.end(),std::back_inserter(folders_todo),
      [root_folder](const std::string& foldername)
      {
        const std::string folder_here {
          root_folder + GetPathSeperator() + foldername
        };
        assert(IsFolder(folder_here));
        return folder_here;
      }
    );
  }

  //Search through all sub folders
  while (!folders_todo.empty())
  {
    const std::string folder_todo {
      folders_todo.back() //Read from the back, so push_back can be used
    };
    //Done with this folder
    folders_todo.pop_back();

    #ifndef NDEBUG
    if(!(folders_todo.empty() || folders_todo.back() != folder_todo))
    {
      TRACE("ERROR");
      for (const std::string& todo: folders_todo) { TRACE(todo); }
      for (const std::string& result: v) { TRACE(result); }
    }
    #endif
    assert( (folders_todo.empty() || folders_todo.back() != folder_todo)
      && "Next folder must not be the one that is just processed");


    const std::vector<std::string> files_here {
      GetFilesInFolder(folder_todo)
    };

    const std::vector<std::string> folders_here {
      GetFoldersInFolder(folder_todo)
    };
    #ifndef NDEBUG
    for (const std::string& folder_here: folders_here) { TRACE(folder_here); }
    #endif

    //Copy the files and folders with path added
    std::transform(files_here.begin(),files_here.end(),std::back_inserter(v),
      [folder_todo](const std::string& filename)
      {
        const std::string file_here {
          folder_todo + GetPathSeperator() + filename
        };
        assert(IsRegularFile(file_here));
        return file_here;
      }
    );
    std::transform(folders_here.begin(),folders_here.end(),std::back_inserter(folders_todo),
      [folder_todo](const std::string& foldername)
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

std::vector<std::string> ribi::fileio::GetFilesInFolderByRegex(
  const std::string& folder,
  const std::string& regex_str)
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
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex
  const boost::xpressive::sregex rex = boost::xpressive::sregex::compile(regex_str);

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

std::vector<std::string> ribi::fileio::GetFoldersInFolder(const std::string& folder)
{
  assert(IsFolder(folder));
  QDir dir(folder.c_str());
  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot   );
  const QFileInfoList list = dir.entryInfoList();

  //Convert QFileInfoList to std::vector<std::string> of filenames
  std::vector<std::string> v;
  const int size = list.size();
  for (int i = 0; i != size; ++i)
  {
    const std::string folder_name = list.at(i).fileName().toStdString();
    assert(!folder_name.empty());
    v.push_back(folder_name);
  }
  #ifndef NDEBUG
  for (const std::string s: v)
  {
    assert(std::count(v.begin(),v.end(),s) == 1
      && "Every folder name is unique");
  }
  #endif
  return v;
}

std::string ribi::fileio::GetPath(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

std::string ribi::fileio::GetPathSeperator() noexcept
{
  #ifdef _WIN32
  return "\\";
  #else
  return "/";
  #endif
}

std::string ribi::fileio::GetSuperFolder(const std::string& folder)
{
  const int a = folder.rfind("\\",folder.size());
  const int b = folder.rfind("/",folder.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(folder.size()));
  return
    i == static_cast<int>(std::string::npos)
    ? std::string("")
    : folder.substr(0,i);
}

std::string ribi::fileio::GetTempFileName(const std::string& post)
{
  //Limit the number of searches, to prevent the program from freezing
  //It might occur that the first random names are taken, because
  //of working without a randomize timer first
  for (int i=0; i!=1000; ++i)
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
  throw std::runtime_error("Could not find a temporary file name");
}


std::string ribi::fileio::GetTempFolderName()
{
  //Limit the number of searches, to prevent the program from freezing
  //It might occur that the first random names are taken, because
  //of working without a randomize timer first
  for (int i=0; i!=1000; ++i)
  {
    std::stringstream s;
    s << "tmpfoldername"
      << std::rand()
      << std::rand()
      << std::rand()
      << std::rand();
    if (!IsFolder(s.str())) return s.str();
  }
  throw std::runtime_error("Could not find a temporary folder name");
}

std::string ribi::fileio::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::fileio::GetVersionHistory() noexcept
{
  return {
    "2013-10-14: Version 1.0: initial version",
    "2013-11-08: Version 1.1: improved FileToVector, improved GetFileBasename, added some functions",
    "2013-12-10: Version 1.2: improved existing function, added some functions"
  };
}

bool ribi::fileio::IsFolder(const std::string& filename) noexcept
{
  return QDir(filename.c_str()).exists();
}

bool ribi::fileio::IsRegularFile(const std::string& filename) noexcept
{
  return !QDir(filename.c_str()).exists() && QFile::exists(filename.c_str());
}

std::string ribi::fileio::RemovePath(const std::string& filename)
{
  std::vector<std::size_t> v;
  const std::size_t a = filename.rfind("\\",filename.size());
  if (a != std::string::npos) v.push_back(a);
  const std::size_t b = filename.rfind("/",filename.size());
  if (b != std::string::npos) v.push_back(b);
  if (v.empty()) return filename;
  const std::size_t i = *std::max_element(v.begin(),v.end());
  assert(i < filename.size());
  const std::size_t j = i + 1;
  assert(j < filename.size());
  const std::string s = filename.substr(j,filename.size() - j);
  return s;
}

void ribi::fileio::RenameFile(
  const std::string& from,
  const std::string& to,
  const RenameMode rename_mode)
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
  const int result = std::rename(from.c_str(),to.c_str());
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

#ifndef NDEBUG
void ribi::fileio::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::fileio::Test");
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
    assert(GetFileBasename("") == std::string(""));
    assert(GetFileBasename("tmp") == std::string("tmp"));
    assert(GetFileBasename("tmp.") == std::string("tmp"));
    assert(GetFileBasename("tmp.x") == std::string("tmp"));
    assert(GetFileBasename("tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("tmp.text") == std::string("tmp"));
    assert(GetFileBasename("tmp.longextension") == std::string("tmp"));
    assert(GetFileBasename("input_triangle.txt") == std::string("input_triangle"));
    assert(GetFileBasename("tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder\\tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder/tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder/tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder\\tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/My-Folder\\tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/My_Folder\\tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameConnectThree")
      == std::string("GameConnectThree"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameAminoAcidFighter")
      == std::string("GameAminoAcidFighter"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameK3OpEenRij")
      == std::string("GameK3OpEenRij"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Projects/ProjectRichelBilderbeek")
      == std::string("ProjectRichelBilderbeek"));
  }
  //GetExtension
  {
    assert(GetExtensionNoDot("") == std::string(""));
    assert(GetExtensionNoDot("tmp") == std::string(""));
    assert(GetExtensionNoDot("tmp.") == std::string(""));
    assert(GetExtensionNoDot("tmp.x") == std::string("x"));
    assert(GetExtensionNoDot("tmp.txt") == std::string("txt"));
    assert(GetExtensionNoDot("tmp.text") == std::string("text"));
    assert(GetExtensionNoDot("tmp.longextension") == std::string("longextension"));
    assert(GetExtensionNoDot("input_triangle.txt") == std::string("txt"));
    assert(GetExtensionNoDot("tmp") == std::string(""));
    assert(GetExtensionNoDot("MyFolder/tmp") == std::string(""));
    assert(GetExtensionNoDot("MyFolder/tmp.txt") == std::string("txt"));
    assert(GetExtensionNoDot("MyFolder\\tmp.txt") == std::string("txt"));
    assert(GetExtensionNoDot("MyFolder/MyFolder/tmp") == std::string(""));
    assert(GetExtensionNoDot("MyFolder/MyFolder/tmp.txt") == std::string("txt"));
    assert(GetExtensionNoDot("MyFolder/MyFolder\\tmp.txt") == std::string("txt"));
    assert(GetExtensionNoDot("MyFolder/My-Folder\\tmp.txt") == std::string("txt"));
    assert(GetExtensionNoDot("MyFolder/My_Folder\\tmp.txt") == std::string("txt"));

    assert(GetExtensionWithDot("") == std::string(""));
    assert(GetExtensionWithDot("tmp") == std::string(""));
    assert(GetExtensionWithDot("tmp.") == std::string("."));
    assert(GetExtensionWithDot("tmp.x") == std::string(".x"));
    assert(GetExtensionWithDot("tmp.txt") == std::string(".txt"));
    assert(GetExtensionWithDot("tmp.text") == std::string(".text"));
    assert(GetExtensionWithDot("tmp.longextension") == std::string(".longextension"));
    assert(GetExtensionWithDot("input_triangle.txt") == std::string(".txt"));
    assert(GetExtensionWithDot("tmp") == std::string(""));
    assert(GetExtensionWithDot("MyFolder/tmp") == std::string(""));
    assert(GetExtensionWithDot("MyFolder/tmp.txt") == std::string(".txt"));
    assert(GetExtensionWithDot("MyFolder\\tmp.txt") == std::string(".txt"));
    assert(GetExtensionWithDot("MyFolder/MyFolder/tmp") == std::string(""));
    assert(GetExtensionWithDot("MyFolder/MyFolder/tmp.txt") == std::string(".txt"));
    assert(GetExtensionWithDot("MyFolder/MyFolder\\tmp.txt") == std::string(".txt"));
    assert(GetExtensionWithDot("MyFolder/My-Folder/tmp.txt") == std::string(".txt"));
    assert(GetExtensionWithDot("MyFolder/My_Folder\\tmp.txt") == std::string(".txt"));

    assert(GetExtension("") == std::string(""));
    assert(GetExtension("tmp") == std::string(""));
    assert(GetExtension("tmp.") == std::string("."));
    assert(GetExtension("tmp.x") == std::string(".x"));
    assert(GetExtension("tmp.txt") == std::string(".txt"));
    assert(GetExtension("tmp.text") == std::string(".text"));
    assert(GetExtension("tmp.longextension") == std::string(".longextension"));
    assert(GetExtension("input_triangle.txt") == std::string(".txt"));
    assert(GetExtension("tmp") == std::string(""));
    assert(GetExtension("MyFolder/tmp") == std::string(""));
    assert(GetExtension("MyFolder/tmp.txt") == std::string(".txt"));
    assert(GetExtension("MyFolder\\tmp.txt") == std::string(".txt"));
    assert(GetExtension("MyFolder/MyFolder/tmp") == std::string(""));
    assert(GetExtension("MyFolder/MyFolder/tmp.txt") == std::string(".txt"));
    assert(GetExtension("MyFolder/MyFolder\\tmp.txt") == std::string(".txt"));
    assert(GetExtension("MyFolder/My_Folder/tmp.txt") == std::string(".txt"));
    assert(GetExtension("MyFolder/My-Folder\\tmp.txt") == std::string(".txt"));
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
    assert(RemovePath("x.txt") == std::string("x.txt"));
    assert(RemovePath("MyFolder/x.txt") == std::string("x.txt"));
    assert(RemovePath("Another/MyFolder/x.txt") == std::string("x.txt"));
    assert(RemovePath("Yet/Another/MyFolder/x.txt") == std::string("x.txt"));
    assert(RemovePath("MyFolder\\x.txt") == std::string("x.txt"));
    assert(RemovePath("Another\\MyFolder\\x.txt") == std::string("x.txt"));
    assert(RemovePath("Yet\\Another\\MyFolder\\x.txt") == std::string("x.txt"));
    assert(RemovePath("Another/MyFolder\\x.txt") == std::string("x.txt"));
    assert(RemovePath("Another\\MyFolder/x.txt") == std::string("x.txt"));
    assert(RemovePath("Yet\\Another/MyFolder\\x.txt") == std::string("x.txt"));
    assert(RemovePath("Yet\\Another\\MyFolder/x.txt") == std::string("x.txt"));
    assert(RemovePath("Yet\\An-other\\MyFolder/x.txt") == std::string("x.txt"));
    assert(RemovePath("Yet\\An_other\\MyFolder/x.txt") == std::string("x.txt"));
    assert(RemovePath("Yet\\Another\\MyFolder/x_y.txt") == std::string("x_y.txt"));
    assert(RemovePath("Yet\\Another\\MyFolder/x-y.txt") == std::string("x-y.txt"));
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
  TRACE("Finished ribi::fileio::Test successfully");
}
#endif

void ribi::fileio::VectorToFile(
  const std::vector<std::string>& v,
  const std::string& filename,
  const CopyMode copy_mode
)
{
  if (copy_mode == CopyMode::prevent_overwrite)
  {
    assert(!IsRegularFile(filename) && "File must not exist");
    if (IsRegularFile(filename))
    {
      std::stringstream msg;
      msg
        << "VectorToFile: not allowed to overwrite file '"
        << filename
        << "'";

      throw std::runtime_error(msg.str().c_str());
    }
  }
  {
    std::ofstream f(filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  }
  assert(IsRegularFile(filename));
}
