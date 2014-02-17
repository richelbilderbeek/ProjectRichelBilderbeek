#include <cassert>
#include <fstream>


///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFile(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

int main()
{
  const std::string before = "a.tmp";
  const std::string after  = "b.tmp";

  //Delete possible previous files
  std::remove(before.c_str());
  std::remove(after.c_str());
  assert(!IsRegularFile(before));
  assert(!IsRegularFile(after));

  //Create before
  {
    std::ofstream f(before.c_str());
  }
  assert( IsRegularFile(before));
  assert(!IsRegularFile(after));

  //Rename before to after
  {
    std::rename(before.c_str(),after.c_str());
  }
  assert(!IsRegularFile(before));
  assert( IsRegularFile(after));

  //Delete files
  std::remove(before.c_str());
  std::remove(after.c_str());
  assert(!IsRegularFile(before));
  assert(!IsRegularFile(after));
}
