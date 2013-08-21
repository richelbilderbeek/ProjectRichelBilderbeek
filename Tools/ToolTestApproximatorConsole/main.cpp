#include "approximator.h"

int main()
{
  Approximator<double,double> a;
  Approximator<double,int> b;
  b.Add(1.0,123);
  b.Approximate(2.0);
}
