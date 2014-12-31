#include <iostream>

struct Base
{
  virtual ~Base() noexcept {}
  virtual void A() const = 0;
  virtual void B() const = 0;
};

struct Derived : public Base
{
  void A() const override final { std::cout << "Derived::A\n"; } //A is final
  virtual void B() const override { std::cout << "Derived::B\n"; }
};

struct DerivedAgain : public Derived
{
  //void MakeSound() const { std::cout << "DerivedAgain::A\n"; } //will not compile: Derived::A is final
  void B() const override { std::cout << "DerivedAgain::B\n"; }
};

int main()
{
  Derived d;
  d.A();
  d.B();

  DerivedAgain da;
  da.A();
  da.B();
}
