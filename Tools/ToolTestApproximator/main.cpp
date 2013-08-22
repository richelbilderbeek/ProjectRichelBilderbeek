#include "approximator.h"

int main()
{
  Approximator<double,int> a;
  a.Add(1.0,123);
  a.Add(3.0,234);
  std::cout << a.Approximate(2.0) << '\n';
}
