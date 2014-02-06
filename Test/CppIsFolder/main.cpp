#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDir>

#include <boost/filesystem.hpp>
#pragma GCC diagnostic pop


///Returns if the name is a folder name
//From http://www.richelbilderbeek.nl/CppIsFolder.htm
bool IsFolderBoostFilesystem(const std::string& filename)
{
  return boost::filesystem::is_directory(filename);
}

///Returns if the name is a folder name
///From http://www.richelbilderbeek.nl/CppIsFolder.htm
bool IsFolderQt(const std::string& filename)
{
  return QDir(filename.c_str()).exists();
}

int main(int, char * argv[])
{
  assert(!IsFolderBoostFilesystem(argv[0]));
  assert(!IsFolderQt(argv[0]));

  assert(IsFolderBoostFilesystem("../CppIsFolder"));
  assert(IsFolderQt("../CppIsFolder"));

  assert(!IsFolderBoostFilesystem("tempfolder"));
  assert(!IsFolderQt("tempfolder"));

  QDir().mkdir("tempfolder");

  assert(IsFolderBoostFilesystem("tempfolder"));
  assert(IsFolderQt("tempfolder"));

  QDir().rmdir("tempfolder");

  assert(!IsFolderBoostFilesystem("tempfolder"));
  assert(!IsFolderQt("tempfolder"));

  assert(!IsFolderBoostFilesystem(":/images/R.png"));
  assert(!IsFolderQt(":/images/R.png"));
}
