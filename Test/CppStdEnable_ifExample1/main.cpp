//Adapted from http://www.cplusplus.com/reference/type_traits/enable_if

// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<
  std::is_integral<T>::value,bool>::type
  is_odd(const T i)
{
  return static_cast<bool>(i%2);
}

// 2. the second template argument is only valid if T is an integral type:
template <class T,
  class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i)
{
  return !static_cast<bool>(i%2);
}

int main()
{
  const int i = 1; //code does not compile if type of i is not integral
  std::cout
    << "i is odd : " << is_odd(i) << '\n'
    << "i is even: " << is_even(i) << '\n';
}
