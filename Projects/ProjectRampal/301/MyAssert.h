#ifndef BILDERBIKKEL_ASSERT_H
#define BILDERBIKKEL_ASSERT_H
//---------------------------------------------------------------------------
#include <cassert>

//From http://www.richelbilderbeek.nl/CppAssert.htm
#ifdef NDEBUG_BILDERBIKKEL
  #define Assert(x) ((void)0)
#else
  #include <cstdlib>
  #include <fstream>
  #include <iostream>
  #include <stdexcept>

  #define Assert(x)                      \
  if (!(x))                              \
  {                                      \
    std::cout                            \
      << "ERROR!! Assertion "            \
      <<  std::string (#x)               \
      <<  " failed\n on line "           \
      <<  (__LINE__)                     \
      <<  "\n in file "                  \
      <<  __FILE__                       \
      << std::endl;                      \
    std::ofstream f("assert_out.txt");   \
    f                                    \
      << "ERROR!! Assertion "            \
      <<  std::string (#x)               \
      <<  " failed\n on line "           \
      <<  (__LINE__)                     \
      <<  "\n in file "                  \
      <<  __FILE__                       \
      << std::endl;                      \
    f.close();                           \
    std::exit(1234);                     \
    throw std::logic_error(              \
      "Assertion failed");               \
  }

#endif
//---------------------------------------------------------------------------
#endif // BILDERBIKKEL_ASSERT_H
