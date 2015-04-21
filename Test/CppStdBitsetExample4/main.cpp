#include <iostream>
#include <bitset>
#include <cassert>
#include <fstream>
#include <vector>

typedef std::bitset<8> Bitset;
const int n_bitsets{2};
Bitset v[n_bitsets];
Bitset w[n_bitsets];


void BitsetsToFile(
  const Bitset bitsets[n_bitsets],
  const std::string& filename)
{
  std::ofstream f(filename.c_str());
  for (int i=0; i!=n_bitsets; ++i) { f << bitsets[i] << '\n'; }
}

Bitset * FileToBitsets(const std::string& filename)
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

  Bitset * const array{new Bitset[n_bitsets]};
  for (int i=0; i!=n_bitsets; ++i) { array[i] = v[i]; }
  return array;

}

int main()
{
  const Bitset b0(std::string("01010101"));
  const Bitset b1(std::string("10101011"));
  v[0] = b0;
  v[1] = b1;

  const std::string filename{"tmp.txt"};
  BitsetsToFile(v,filename);

  const Bitset * w{FileToBitsets(filename)};
  if (v != w)
  {
    std::cout << "v:" << '\n';
    for (const auto& b: v) { std::cout << b << '\n'; }
    std::cout << "w:" << '\n';
    for (int i=0; i!=n_bitsets; ++i) { std::cout << w[i] << '\n'; }
  }
  assert(*v == *w);
}
