#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "fileio.h"

#include <cassert>
#include <fstream>

#include <boost/xpressive/xpressive.hpp>

#include <QDir>
#include <QFile>

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
  std::remove(filename.c_str());
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
  const std::string cmd = "rmdir " + folder;
  const int error = std::system(cmd.c_str());
  assert(!error && "Assume rmdir works under both Windows and Linux");
  if (error)
  {
    throw std::runtime_error("DeleteFolder failed by system call");
  }
  if (IsFolder(folder))
  {
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

const std::vector<std::string> ribi::fileio::FileToVector(const std::string& filename)
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
  return v;
}

const std::string ribi::fileio::GetExtension(const std::string& filename)
{
  return GetExtensionWithDot(filename);
}

const std::string ribi::fileio::GetExtensionNoDot(const std::string& filename)
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

const std::string ribi::fileio::GetExtensionWithDot(const std::string& filename)
{
  return
    ( std::count(filename.begin(),filename.end(),'.')
    ? std::string(".")
    : std::string("")
    )
    + GetExtensionNoDot(filename);
}

const std::string ribi::fileio::GetFileBasename(const std::string& filename)
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

const std::vector<std::string> ribi::fileio::GetFilesInFolder(const std::string& folder)
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

const std::vector<std::string> ribi::fileio::GetFilesInFolderByRegex(
  const std::string& folder,
  const std::string& regex_str)
{
  //Get all filenames
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

const std::string ribi::fileio::GetPath(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

const std::string ribi::fileio::GetPathSeperator() noexcept
{
  #ifndef WIN32
  return "\\";
  #else
  return "/";
  #endif
}

const std::string ribi::fileio::GetSuperFolder(const std::string& folder)
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

const std::string ribi::fileio::GetTempFileName()
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
      << std::rand();
    if (!IsRegularFile(s.str())) return s.str();
  }
  throw std::runtime_error("Could not find a temporary file name");
}


const std::string ribi::fileio::GetTempFolderName()
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

const std::string ribi::fileio::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::fileio::GetVersionHistory() noexcept
{
  return {
    "2013-10-14: Version 1.0: initial version",
    "2013-11-08: Version 1.1: improved FileToVector, improved GetFileBasename, added some functions"
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

const std::string ribi::fileio::RemovePath(const std::string& filename)
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
    const std::string filename { "tmp.txt" };
    const std::string filename_copy { "tmp_copy.txt" };
    DeleteFile(filename);
    DeleteFile(filename_copy);

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

    assert(!IsRegularFile(filename));
    assert(!IsRegularFile(filename_copy));
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
      assert(!IsFolder(f));
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
      assert(!IsFolder(super_folder));
    }
  }
  //FilesAreIdentical
  {
    const std::vector<std::string> filenames { "tmp_a.txt", "tmp_b.txt", "tmp_c.txt" };
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
      const std::string filename { "tmp.txt" };
      DeleteFile(filename);

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

      assert(!IsRegularFile(filename));
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
    const std::string filename_from = "tmp.txt";
    const std::string filename_to   = "tmp2.txt";

    //Delete possible old temporary files
    DeleteFile(filename_from);
    DeleteFile(filename_to);

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
  }
  TRACE("Finished ribi::fileio::Test successfully");
}
#endif
