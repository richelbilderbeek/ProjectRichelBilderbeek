#include <iostream>
#include <bitset>
#include <cassert>
#include <fstream>
#include <vector>

void BitsetsToFile(
  const std::vector<std::bitset<8>>& bitsets,
  const std::string& filename)
{
  std::ofstream f(filename.c_str());
  for (const auto& bitset: bitsets) { f << bitset << '\n'; }
}

std::vector<std::bitset<8>> FileToBitsets(const std::string& filename)
{
  std::ifstream f(filename.c_str());
  std::vector<std::bitset<8>> v;
  std::ifstream in(filename.c_str());
  for (int i=0; !in.eof(); ++i)
  {
    std::string s;
    std::getline(in,s);
    std::bitset<8> bitset(s);
    v.push_back(bitset);
  }
  assert(!v.empty());
  v.pop_back(); //If this is omitted, a "00000000" is added to back of std::vector
  return v;

}

int main()
{
  typedef std::bitset<8> Bitset;
  typedef std::vector<Bitset> Bitsets;
  const Bitset b1(std::string("01010101"));
  const Bitset b2(std::string("10101011"));
  const Bitsets v = { b1, b2};

  const std::string filename{"tmp.txt"};
  BitsetsToFile(v,filename);

  const Bitsets w{FileToBitsets(filename)};
  if (v != w)
  {
    std::cout << "v:" << '\n';
    for (const auto& b: v) { std::cout << b << '\n'; }
    std::cout << "w:" << '\n';
    for (const auto& b: w) { std::cout << b << '\n'; }
  }
  assert(v == w);
}
