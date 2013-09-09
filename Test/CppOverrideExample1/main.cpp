#include <iostream>

struct Base
{
  virtual void a() const = 0;
  virtual void b() const { std::cout << "Base::b\n"; }
  void c() const { std::cout << "Base::c\n";}
};

struct Derived : public Base
{
  //Implementation of abstract interface
  void a() const { std::cout << "Derived::a\n"; }

  //Override of virtual member function
  virtual void b() const override { std::cout << "Derived::b\n"; }

  //Override of regular member function
  //?Does not override? Similar example as
  //  Stroustrup, The C++ Programming Language, 4th edition, page 590
  //void c() const override { std::cout << "Derived::c\n"; }
};


int main()
{
  const Derived d;
  d.a();
  d.b();
  d.c();
}
