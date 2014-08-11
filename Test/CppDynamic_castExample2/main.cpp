#include <cassert>

struct Base
{
  virtual ~Base() {}
};

struct Derived : public Base { };

int main()
{
  //Base initialized with derived, can be downcasted to derived
  {
    Base * const p1 = new Derived;
    Derived * const p2 = dynamic_cast<Derived*>(p1);
    assert(p1);
    assert(p2);
    assert(p1 == p2);
    delete p1;
    //delete p2; //Do not re-delete!
  }
  //Base initialized with base, cannot be downcasted to derived
  {
    Base * const p1 = new Base;
    Derived * const p2 = dynamic_cast<Derived*>(p1);
    assert( p1);
    assert(!p2);
    assert(p1 != p2);
    delete p1;
  }
  //Const base initialized with derived, can be downcasted to const derived
  {
    Base * const p1 = new Derived;
    const Derived * const p2 = dynamic_cast<const Derived*>(p1);
    assert(p1);
    assert(p2);
    assert(p1 == p2);
    delete p1;
    //delete p2; //Do not re-delete!
  }
  //Const base initialized with base, cannot be downcasted to const derived
  {
    const Base * const p1 = new Base;
    const Derived * const p2 = dynamic_cast<const Derived*>(p1);
    assert( p1);
    assert(!p2);
    assert(p1 != p2);
    delete p1;
  }
  //Const base initialized with derived, cannot be down- and const-casted to non-const derived
  {
    const Base * const p1 = new Derived;
    //Removing const: will and should not compile
    //Derived * const p2 = dynamic_cast<Derived*>(p1));
    assert(p1);
    delete p1;
  }
  //Base initialized with derived, can be downcasted to const derived with adding constness
  {
    const Base * const p1 = new Derived;
    //Adding const: will and should compile
    const Derived * const p2 = dynamic_cast<const Derived*>(p1);
    assert(p1);
    assert(p2);
    assert(p1 == p2);
    delete p1;
    //delete p2; //Do not re-delete!
  }
}
