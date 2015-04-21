#include <bitset>
#include <cassert>

std::bitset<8> StrToBitset(const std::string& s)
{
  std::bitset<8> b(s);
  return b;
}

std::string BitsetToStr(const std::bitset<8>& b)
{
  return b.to_string();
}

int main()
{
  std::string s("01010101");
  assert(s.size() == 8);
  const std::bitset<8> b(StrToBitset(s));
  assert(s == BitsetToStr(b));
}
