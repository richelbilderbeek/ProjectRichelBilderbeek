#include <cassert>
#include <cstdio>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>
#pragma GCC diagnostic pop

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFileBoostFilesystem(const std::string& filename)
{
  return boost::filesystem::is_regular_file(filename);
}

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFileStl(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

int main(int /* argc */, char * argv[])
{
  assert(IsRegularFileBoostFilesystem(argv[0]));
  assert(IsRegularFileStl(argv[0]));

  {
    //Create a regular file
    assert(!IsRegularFileBoostFilesystem("tmp.txt"));
    assert(!IsRegularFileStl("tmp.txt"));
    {
      std::fstream f;
      f.open("tmp.txt",std::ios::out);
      f << "TEMP TEXT";
      f.close();
    }
    assert(IsRegularFileBoostFilesystem("tmp.txt"));
    assert(IsRegularFileStl("tmp.txt"));

    std::remove("tmp.txt");

    assert(!IsRegularFileBoostFilesystem("tmp.txt"));
    assert(!IsRegularFileStl("tmp.txt"));
  }
  {
    //Create a folder
    std::system("mkdir tmp");
    assert(!IsRegularFileBoostFilesystem("tmp"));
    assert(!IsRegularFileStl("tmp"));
    std::system("rmdir tmp");
  }
}
