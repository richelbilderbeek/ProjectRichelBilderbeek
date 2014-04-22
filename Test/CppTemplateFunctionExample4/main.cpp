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

int main()
{
  const int x = 42;
  const double * const p  = new double(123.456);

  std::cout << x << '\n';
  std::cout << p << '\n';

  Cout(x);
  Cout(p);
}

/* Screen output:

42
0x802808
42
123.456
Press <RETURN> to close this window...

*/
