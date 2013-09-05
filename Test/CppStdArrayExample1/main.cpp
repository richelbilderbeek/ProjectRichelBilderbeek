#include <array>
#include <cassert>

int main()
{
  {
    const int sz = 3;
    const std::array<int,sz> v { 0,1,2 };
    static_assert(v.size() == sz,"Can be checked at compile time");
    assert(v[0] == 0);
    assert(v[1] == 1);
    assert(v[2] == 2);
  }
  {
    const int sz = 3;
    const std::array<int,sz> v { 0,1 }; //Oops, forgot the third element
    static_assert(v.size() == sz,"Can be checked at compile time");
    assert(v[0] == 0);
    assert(v[1] == 1);
    assert(v[2] == 0); //Initialized to zero
  }
  //const std::array<int,3> x = { 0,1,2,3 }; //Does not compile: too many elements is checked in assignment
}
