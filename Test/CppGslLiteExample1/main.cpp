#include <gsl_lite.h>

#include <iostream>


void f(Guide::not_null<int*> i)
{
  std::cout << (*i) << std::endl;
}

int main ()
{
  int * p = new int(3);
  f(p);
  //f(nullptr); //Does not compile, which is awesome
  delete p;
  p = nullptr;
  f(p);
}
