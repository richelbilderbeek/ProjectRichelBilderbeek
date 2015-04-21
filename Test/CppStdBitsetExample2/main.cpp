#include <bitset>
#include <cassert>
#include <fstream>

void BitsetToFile(
  const std::bitset<8>& bitset,
  const std::string& filename)
{
  std::ofstream f(filename.c_str());
  f << bitset;
}

std::bitset<8> FileToBitset(const std::string& filename)
{
  std::ifstream f(filename.c_str());
  std::bitset<8> bitset;
  f >> bitset;
  return bitset;
}


int main()
{
  const std::bitset<8> b(std::string("01010101"));
  const std::string filename{"tmp.txt"};
  BitsetToFile(b,filename);

  const std::bitset<8> c{FileToBitset(filename)};
  assert(b == c);
}
