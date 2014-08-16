#include <type_traits>

int main()
{
  static_assert(!std::is_pointer<int >::value,"int  is not a pointer");
  static_assert( std::is_pointer<int*>::value,"int* is     a pointer");
}
