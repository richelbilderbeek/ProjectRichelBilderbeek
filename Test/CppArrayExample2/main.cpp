#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

int main()
{
  {
    const int sz = 5;
    int v[sz];
    assert(sizeof(v) / sizeof(int) == sz);
  }
  {
    const int sz = (std::rand() % 2) - 100;
    assert(sz < 0 && "sz will always be negative, yet I can create an array of this size");
    int v[sz]; //Will be accepted
    assert(static_cast<int>(sizeof(v) / sizeof(int)) == sz); //Will not protect you
    //v[0] = 0; //Crashes the program
  }
    {
      const int sz = (std::rand() % 2) - 100;
      assert(sz < 0 && "sz will always be negative, yet I can create an array of this size");
      std::vector<int> v(sz); //Throws std::bad_alloc
    }
}
