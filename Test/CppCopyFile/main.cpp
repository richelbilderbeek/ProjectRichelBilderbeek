#include <cassert>
#include <fstream>
#include <stdexcept>

#ifdef BOOST_H
#include <boost/filesystem.hpp>
#endif

#ifdef VCL_H
#include <SysUtils.hpp>
#endif

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFile(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

//From http://www.richelbilderbeek.nl/CppCopyFile.htm
void CopyFileStl(const std::string& fileNameFrom, const std::string& fileNameTo)
{
  assert(IsRegularFile(fileNameFrom));
  if(IsRegularFile(fileNameTo))
  {
    throw std::logic_error("Cannot copy over an existing file");
  }
  std::ifstream in (fileNameFrom.c_str());
  std::ofstream out(fileNameTo.c_str());
  out << in.rdbuf();
  out.close();
  in.close();
}

#ifdef BOOST_H
//From http://www.richelbilderbeek.nl/CppCopyFile.htm
void CopyFileBoost(const std::string& from, const std::string& to)
{
  assert(IsRegularFile(fileNameFrom));
  //Boost will check if the copy is made over an existing file
  boost::filesystem::copy_file(from,to);
}
#endif

#ifdef VCL_H
//From http://www.richelbilderbeek.nl/CppCopyFile.htm
void CopyFileVcl(const std::string& from, const std::string& to, const bool failIfExists)
{
  //Use VCL its CopyFile
  CopyFile("FileFrom.txt","FileTo.txt",failIfExists);
}
#endif

int main(int, char* argv[])
{
  const std::string tmp_filename = "temp.txt";

  //Delete file (in case it exists)
  std::remove(tmp_filename.c_str());

  //Copy file
  CopyFileStl(argv[0],tmp_filename);
  assert(IsRegularFile(tmp_filename));

  //Clean up temp file by deleting it
  std::remove(tmp_filename.c_str());

}

