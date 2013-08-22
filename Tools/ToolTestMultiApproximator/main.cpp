#include "approximator.h"
#include "multiapproximator.h"
#include <iostream>

int main()
{
  {
    Approximator<double,int> a;
    //a.Add(1.0,122); //Cannot do this with an Approximator
    a.Add(1.0,123);
    //a.Add(1.0,124); //Cannot do this with an Approximator
    a.Add(3.0,234);
    std::cout << a.Approximate(2.0) << '\n';
  }
  {
    MultiApproximator<double,int> a;
    a.Add(1.0,122);
    a.Add(1.0,123);
    a.Add(1.0,124);
    a.Add(3.0,234);
    std::cout << a.Approximate(2.0) << '\n';
  }
}
