#include <iostream>

struct HappySayHello
{
  void SayHello() const { std::cout << "Hello!\n"; }

protected:
  ~HappySayHello()
  {
    // The destructor of a policy class should be protected and non-virtual:
    // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules,
    //   guidelines, and best practices. ISBN: 0-32-111358-6. Item 50: 'Make
    //   base class destructors public and virtual, or protected and nonvirtual'
    // * Andrei Alexandrescu. Modern C++ Design. 2001. ISBN: 0201704315.
    //   Page 13. Section 1.7: 'The lightweight, effective solution that
    //   policies should use is to define a nonvirtual protected destructor'
  }
};

struct GrumpySayHello
{
  void SayHello() const { std::cout << "Moi\n"; }

protected:
  ~GrumpySayHello()
  {
    // The destructor of a policy class should be protected and non-virtual:
    // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules,
    //   guidelines, and best practices. ISBN: 0-32-111358-6. Item 50: 'Make
    //   base class destructors public and virtual, or protected and nonvirtual'
    // * Andrei Alexandrescu. Modern C++ Design. 2001. ISBN: 0201704315.
    //   Page 13. Section 1.7: 'The lightweight, effective solution that
    //   policies should use is to define a nonvirtual protected destructor'
  }

};

template <class SayHelloPolicy>
class HostClass : public SayHelloPolicy
{
  //Obtains its methods from its SayHelloPolicy
};


int main()
{
  HostClass<HappySayHello> happy;
  happy.SayHello();

  HostClass<GrumpySayHello> grumpy;
  grumpy.SayHello();
}
