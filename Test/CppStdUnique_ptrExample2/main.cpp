#include <iostream>
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>


struct MyClass
{
  MyClass() {}

  static void Deleter(const MyClass * const p) { boost::checked_delete(p); }

  private:
  ~MyClass() { std::cout << "Destructor" << '\n'; }
  friend void boost::checked_delete<>(MyClass* x);
  friend void boost::checked_delete<>(const MyClass* x);
};

int main()
{
  {
    //Use of auto and lambda expression
    const auto deleter
      = [](const MyClass * const p)
      {
        boost::checked_delete(p);
      };

    const std::unique_ptr<const MyClass, decltype(deleter)> p {
      new MyClass,deleter
    };
  }

  {
    //Use of std::function and static member function
    const std::function<void(const MyClass * const)> deleter = MyClass::Deleter;

    const std::unique_ptr<const MyClass, decltype(deleter)> p {
      new MyClass,deleter
    };
  }
}

/* Screen output

Destructor
Destructor
Press <RETURN> to close this window...

*/
