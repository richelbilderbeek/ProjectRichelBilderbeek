#include <string>
#include <type_traits>

int main()
{
  static_assert( std::is_scalar<int>::value,"An int is a scalar");
  static_assert( std::is_scalar<int*>::value,"An int* is a scalar");
  static_assert(std::is_scalar<double>::value,"A double is a scalar");
  enum MyEnum { A, B};
  static_assert(std::is_scalar<MyEnum>::value,"An enum is a scalar");
  enum class MyEnumClass { A, B};
  static_assert(std::is_scalar<MyEnumClass>::value,"An enum class is a scalar");
  struct MyClass {};
  static_assert(!std::is_scalar<MyClass>::value,"A class is not a scalar");

  static_assert(!std::is_scalar<std::string>::value,"A std::string is not a scalar");
}
