#include <iostream>

struct Final final
{
  void A() const {}
};

// error: cannot derive from 'final' base 'Final' in derived type 'Derived'
// struct Derived : public Final {};

int main()
{
  const Final d;
  d.A();
}
