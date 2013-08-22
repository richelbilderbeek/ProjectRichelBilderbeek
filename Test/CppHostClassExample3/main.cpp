#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <class T>
struct CheckPolicyNotEmpty
{
  void Check(const T& s)
  {
    assert(!s.empty() && "Object must not be empty");
  }

protected:
  ~CheckPolicyNotEmpty()
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

template <class T>
struct CheckPolicyNotNull
{
  void Check(const T& p)
  {
    assert(p && "Pointer must not be null");
  }

protected:
  ~CheckPolicyNotNull()
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

///Manager keeps a std::vector in a valid state
template <class T, typename CheckPolicy>
struct Manager : public CheckPolicy
{
  Manager(const std::vector<T>& v) : m_v(v) { CheckAll(); }

  private:
  std::vector<T> m_v;

  void CheckAll()
  {
    for (const T& t: m_v) this->Check(t);
  }
};

int main()
{
  {
    const std::vector<int *> v
      = { new int, new int, new int };
    //const std::vector<int *> v
    //  = { new int, new int, nullptr }; //nullptr will be detected
    const Manager<int *, CheckPolicyNotNull<int *> > pointers( v );
    for (int * p: v) delete p;
  }
  {
    const Manager<std::string, CheckPolicyNotEmpty<std::string> > strings(
      { "1", "12", "123" } );
    //const Manager<std::string, CheckPolicyNotEmpty<std::string> > strings(
    //  { "1", "12", "" } ); //empty std::string will be detected
  }
}
