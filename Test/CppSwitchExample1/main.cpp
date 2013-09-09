#include <cassert>
#include <iostream>

int main()
{
  const int coin = std::rand() % 2;
  switch (coin)
  {
    case 0: std::cout << "Heads\n"; break;
    case 1: std::cout << "Tails\n" ; break;
    default: assert(!"Should not get here");
  }
}
