#include <cstdlib>
#include <iostream>
#include <type_traits>

template <class T> void Cout(const T* t)
{
  std::cout << (*t) << '\n';
}

template <class T> void Cout(const T& t )
{
  std::cout << (t) << '\n';
}

template <class Container> void Cout(const Container& v)
{
  //How to get this to work?
  for (const Container::value_type t: v)
  {
    Cout<const Container::value_type>(t);
  }
}


int main()
{
  const int x = 42;
  const double * const p  = new double(123.456);
  const std::vector<int *> v { new int(1), new int(2), new int(3) };

  Cout(x);
  Cout(p);

  Cout(v); //How to get this to work?
}

/* Screen output:

*/
