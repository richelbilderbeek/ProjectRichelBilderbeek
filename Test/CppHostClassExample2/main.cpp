#include <fstream>
#include <iostream>
#include <string>

template <typename OutputPolicy>
struct Tracer : public OutputPolicy
{

};

struct OutputPolicyCout
{
  void Trace(const std::string& s)
  {
    std::cout << s << '\n';
  }

protected:
  ~OutputPolicyCout()
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

struct OutputPolicyFile
{
  OutputPolicyFile() : m_file("Trace.txt")
  {

  }

  void Trace(const std::string& s)
  {
    m_file << s << '\n';
  }

  std::ofstream m_file;

protected:

  ~OutputPolicyFile()
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

int main()
{
  Tracer<OutputPolicyCout> p1;
  Tracer<OutputPolicyFile> p2;
  p1.Trace("x");
  p2.Trace("x");
}
