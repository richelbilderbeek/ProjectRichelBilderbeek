#ifndef BILDERBIKKEL_TRACE_H
#define BILDERBIKKEL_TRACE_H
//---------------------------------------------------------------------------
#include <cassert>

//From http://www.richelbilderbeek.nl/CppAssert.htm
#ifdef NTRACE_BILDERBIKKEL
  #define Trace(x) ((void)0)
#else
  #include <fstream>
  #include <iostream>
  #include <stdexcept>

  #define Trace(x)                    \
  {                                   \
    std::ofstream f("trace_out.txt"); \
    f                                 \
      << "TRACE \'"            \
      <<  std::string (#x)               \
      <<  "\' line "           \
      <<  (__LINE__)                     \
      <<  " in file '"                  \
      <<  __FILE__                       \
      <<  "': "                       \
      <<  std::string (x)               \
      <<  "'"                       \
      << std::endl;                      \
    f.close();                           \
    }  \
    std::cout                            \
      << "TRACE \'"            \
      <<  std::string (#x)               \
      <<  "\' line "           \
      <<  (__LINE__)                     \
      <<  " in file '"                  \
      <<  __FILE__                       \
      <<  "': "                       \
      <<  std::string (x)               \
      <<  "'"                       \
      << std::endl;                      \

#endif
//---------------------------------------------------------------------------
#endif // BILDERBIKKEL_TRACE_H
