#include <iostream>

struct MyClass
{
  MyClass(const int x) noexcept : m_x(x) {}
  private:
  const int m_x;
  friend std::ostream& operator<<(std::ostream& os, const MyClass& myClass) noexcept;
};

std::ostream& operator<<(std::ostream& os, const MyClass& myClass) noexcept
{
  os << "MyClass.value: " << myClass.m_x;
  return os;
}

int main()
{
  const MyClass my_class(13);
  std::cout << my_class << '\n';
}

/* Screen output

MyClass.value: 13
Press <RETURN> to close this window...

*/
