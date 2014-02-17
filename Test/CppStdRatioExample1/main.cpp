#include <iostream>
#include <ratio>

int main()
{
  static_assert(std::ratio<7,-21>::num == -1,
    "std::ratio simplifies, takes sign to numerator");
  static_assert(std::ratio<7,-21>::den ==  3,
    "std::ratio simplifies, takes sign to numerator");

  static_assert(std::ratio_add<std::ratio<1,3>,std::ratio<1,6>>::num == 1,"1/3 + 1/6 == 1/2");
  static_assert(std::ratio_add<std::ratio<1,3>,std::ratio<1,6>>::den == 2,"1/3 + 1/6 == 1/2");
}
