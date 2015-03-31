#include <algorithm>
#include <string>
#include <iostream>

char CreateRandomChar()
{
  return 'a' + (std::rand() % 26);
}

std::string CreateRandomString(const int length)
{
  std::string s(length,0);
  std::generate(std::begin(s),std::end(s),CreateRandomChar);
  return s;
}

int main()
{
  for (int i=0; i!=20; ++i)
  {
    std::cout << CreateRandomString(i) << '\n';
  }
}
