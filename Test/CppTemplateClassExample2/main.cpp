#include <iostream>

///Template class
template <class T>
struct MyClass
{
  MyClass(const T& x);
};

///Template class specifialized for int, definition in declaration
template <>
struct MyClass<int>
{
  MyClass(const int& x)
  {
    std::cout << "int: " << x << '\n';
  }
};

///Template class specifialized for int, definition seperate after declaration
template <>
struct MyClass<double>
{
  MyClass(const double& x);
};

MyClass<double>::MyClass(const double& x)
{
  std::cout << "double: " << x << '\n';
}

int main()
{
  const MyClass<int> m(123);
  const MyClass<double> n(3.14);

  //Create a MyClass<bool> fails (correctly) with:
  //undefined reference to 'MyClass<bool>::MyClass(bool const&)'
  //const MyClass<bool> q(true);
}
