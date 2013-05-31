#ifndef MYASSERT_H
#define MYASSERT_H

//From http://www.richelbilderbeek.nl/CppQtAssert.htm
#ifdef MY_NDEBUG
  #define Assert(x) ((void)0)
#else
  #include <iostream>
  #include <stdexcept>

  #define Assert(x)                      \
  if (!(x))                             \
  {                                      \
    std::cout                            \
      << "ERROR!! Assertion "            \
      <<  std::string (#x)               \
      <<  " failed\n on line "           \
      <<  (__LINE__)                     \
      <<  "\n in file "                  \
      <<  __FILE__                       \
      << std::endl;                      \
      throw std::logic_error(            \
        "Assertion failed");             \
  }

#endif

#endif // MYASSERT_H
