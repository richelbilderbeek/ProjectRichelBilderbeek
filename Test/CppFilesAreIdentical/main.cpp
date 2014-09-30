#include <cassert>
#include <fstream>
#include <string>
#include <vector>

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool IsRegularFile(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
std::vector<std::string> FileToVector(const std::string& filename)
{
  assert(IsRegularFile(filename));
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

bool FilesAreIdentical(
  const std::string& filename_a,
  const std::string& filename_b)
{
  const std::vector<std::string> v { FileToVector(filename_a) };
  const std::vector<std::string> w { FileToVector(filename_b) };
  return v == w;
}

int main()
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
