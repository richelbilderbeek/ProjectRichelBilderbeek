#include <array>
#include <cassert>
#include <boost/array.hpp>
#include <tr1/array>

int main()
{
  //Statically allocated plain array
  {
    //const int w[3] = { 0,1 }; //Does compile: too few elements is not checked in assignment
    //const int x[3] = { 0,1,2,3 }; //Does not compile: too many elements is checked in assignment

    const int v[3] = { 0,1,2 };

    static_assert(sizeof(v) / sizeof(int) == 3,"");
    assert(v[1] == 1);
  }
  //Dynamically allocated plain array
  {
    int * const v { new int(3) }; //Cannot initialize directly
    v[0] = 0; v[1] = 1; v[2] = 2;

    static_assert(sizeof(v) / sizeof(int) == 1 || sizeof(v) / sizeof(int) == 2,
      "WARNING: you might have expected this to be 3");
    assert((sizeof(v) / sizeof(int) == 1 || sizeof(v) / sizeof(int) == 2)
      && "WARNING: you might have expected this to be 3");

    assert(v[1] == 1);

    delete[] v; //Do not forget to free memory with right syntax
  }
  //std::tr1::array
  {
    //const std::tr1::array<int,3> w = { 0,1 }; //Does compile: too few elements is not checked in assignment
    //const std::tr1::array<int,3> x = { 0,1,2,3 }; //Does not compile: too many elements is checked in assignment
    const std::tr1::array<int,3> v { 0,1,2 }; //Note the double braces
    //static_assert(v.size() == 3,""); //Not allowed
    assert(v[1] == 1);
  }
  //std::array
  {
    //const std::array<int,3> w = { 0,1 }; //Does compile: too few elements is not checked in assignment
    //const std::array<int,3> x = { 0,1,2,3 }; //Does not compile: too many elements is checked in assignment

    const std::array<int,3> v { 0,1,2 }; //Note the double braces
    static_assert(v.size() == 3,"");
    assert(v[1] == 1);
  }
  //boost::array
  {
    //const boost::array<int,3> w = { 0,1 }; //Does compile: to few elements is not checked in assignment
    //const boost::array<int,3> x = { 0,1,2,3 }; //Does not compile: too many elements is checked in assignment

    const boost::array<int,3> v { 0,1,2 }; //Note the double braces

    //static_assert(v.size() == 3,""); //Not allowed
    assert(v.size() == 3);
    assert(v[1] == 1);
  }
}
