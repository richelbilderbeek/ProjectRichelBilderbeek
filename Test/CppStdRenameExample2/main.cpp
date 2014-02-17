#include <cassert>
#include <fstream>
#include <string>

bool IsRegularFile(const std::string& filename);

///Delete a file
//From http://www.richelbilderbeek.nl/CppDeleteFile.htm
void DeleteFile(const std::string& filename)
{
  std::remove(filename.c_str());
  assert(!IsRegularFile(filename));

}

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
  std::rename(filename_from.c_str(),filename_to.c_str());

  //Only filename_to will exist
  assert(!IsRegularFile(filename_from));
  assert( IsRegularFile(filename_to));

}
