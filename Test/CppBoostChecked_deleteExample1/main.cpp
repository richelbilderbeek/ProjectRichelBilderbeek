#include <iostream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#pragma GCC diagnostic pop

struct MyClass
{
  MyClass(const std::string& bye_message) : m_bye_message{bye_message} {}

  private:
  ~MyClass() { std::cout << m_bye_message << '\n'; }
  friend void boost::checked_delete<>(MyClass* x);
  friend void boost::checked_delete<>(const MyClass* x);

  const std::string m_bye_message;
};

int main()
{
  {
    //const MyClass c; //Will not compile
  }
  {
    const MyClass * const p { new MyClass("raw pointer") };

    //delete p; //Will not compile
    boost::checked_delete(p);
  }
  {
    const boost::scoped_ptr<const MyClass> p { new MyClass("boost::scoped_ptr") };

    //No need to delete p, this is done by boost::scoped_ptr
  }
  {
    const auto deleter
      = [](const MyClass * const p)
      {
        std::cout << "custom deleter" << '\n';
        boost::checked_delete(p);
      };

    const std::unique_ptr<const MyClass, decltype(deleter)> p {
      new MyClass("std::unique_ptr with custom deleter"),
      deleter
    };

    //No need to delete p, this is done by std::unique_ptr its deleter
  }
  {
    const boost::shared_ptr<const MyClass> p {
      new MyClass("boost::shared_ptr")
    };

    //No need to delete p, this is done by boost::shared_ptr
  }
  {
    //Won't compile :(
    //const boost::shared_ptr<const MyClass> p {
    //  boost::make_shared<const MyClass>("boost::shared_ptr")
    //};
  }
}

/* Screen output

raw pointer
boost::scoped_ptr
custom deleter
std::unique_ptr with custom deleter
boost::shared_ptr

*/
