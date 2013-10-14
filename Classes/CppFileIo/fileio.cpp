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
  std::ifstream in (fileNameFrom.c_str());
  std::ofstream out(fileNameTo.c_str());
  out << in.rdbuf();
  out.close();
  in.close();
}

void ribi::fileio::DeleteFile(const std::string& filename)
{
  std::remove(filename.c_str());
  assert(!IsRegularFile(filename));
}

bool ribi::fileio::FilesAreIdentical(
  const std::string& filename_a,
  const std::string& filename_b)
{
  const std::vector<std::string> v { FileToVector(filename_a) };
  const std::vector<std::string> w { FileToVector(filename_b) };
  return v == w;
}

const std::vector<std::string> ribi::fileio::FileToVector(const std::string& filename)
{
  #ifndef NDEBUG
  if (!IsRegularFile(filename))
  {
    TRACE("ERROR");
    TRACE(filename);
  }
  #endif
  assert(IsRegularFile(filename));
  assert(!IsFolder(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

const std::string ribi::fileio::GetExtension(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "(.*)?(\\.[A-Za-z]*)" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[2];
  }

  return "";
}

const std::string ribi::fileio::GetFileBasename(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "((.*)(/|\\\\))?([A-Za-z0-9]*)((\\.)([A-Za-z0-9]*))?" );
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
  TRACE(s);
  return s;
}

void ribi::fileio::RenameFile(
  const std::string& from,
  const std::string& to,
  const RenameMode rename_mode)
{
  assert(IsRegularFile(from) && "Cannot rename a non-existing file");
  assert(from != to && "Cannot rename to the same filename");
  if (rename_mode == RenameMode::prevent_overwrite && IsRegularFile(to))
  {
    throw std::logic_error("Renaming to an existing file is not allowed");
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
    assert(GetFileBasename("tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder\\tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder/tmp") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder/tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("MyFolder/MyFolder\\tmp.txt") == std::string("tmp"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameConnectThree")
      == std::string("GameConnectThree"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameAminoAcidFighter")
      == std::string("GameAminoAcidFighter"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Games/GameK3OpEenRij")
      == std::string("GameK3OpEenRij"));
    assert(GetFileBasename("/home/richel/ProjectRichelBilderbeek/Projects/ProjectRichelBilderbeek")
      == std::string("ProjectRichelBilderbeek"));
  }
  //GetPath
  {
    assert(GetPath("C:\\any_path\\any_file.cpp")=="C:\\any_path");
    assert(GetPath("/any_path/any_file.cpp")=="/any_path");
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
    {
      //Create a folder
      const int mkdir_error = std::system("mkdir tmp");
      assert(!mkdir_error);
      assert(!IsRegularFile("tmp"));
      const int rmdir_error = std::system("rmdir tmp");
      assert(!rmdir_error);
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
}
#endif
