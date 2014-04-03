#include <type_traits>

struct MyClass{};

int main()
{
  static_assert( std::is_compound<MyClass>::value,"MyClass is compound");
  static_assert(!std::is_compound<int>::value,"int is not a compound");
}
