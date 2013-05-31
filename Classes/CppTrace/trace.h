//---------------------------------------------------------------------------
/*
Trace, some tracing macro's
Copyright (C) 2010-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppTrace.htm
//---------------------------------------------------------------------------
#ifndef TRACE_H
#define TRACE_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>

struct Trace
{
  static const std::string GetVersion()
  {
    return "2.5";
  }
  static const std::vector<std::string> GetVersionHistory()
  {
    std::vector<std::string> v;
    v.push_back("2010-xx-xx: Version 1.0: initial version");
    v.push_back("2011-06-22: Version 2.0: added versioning, added boost::lexical_cast in TRACE");
    v.push_back("2011-08-15: Version 2.1: added all #includes");
    v.push_back("2012-01-15: Version 2.2: Moved bracket in TRACE to allow 'if (false) TRACE(true);' without surprises");
    v.push_back("2012-02-01: Version 2.3: put START_TRACE in its own scope");
    v.push_back("2012-08-11: Version 2.4: put #ifdef _WIN32 on top for cross-compiling");
    v.push_back("2013-02-24: Version 2.5: added FTRACE for tracing to file only");
    return v;
  }
};

#ifdef NTRACE_BILDERBIKKEL
  #define START_TRACE() ((void)0)
  #define TRACE(x) ((void)0)
  #define FTRACE(x) ((void)0)
  #define TRACE_FUNC() ((void)0)
#else
  #include <fstream>
  #include <iostream>
  #include <stdexcept>
  #include <boost/lexical_cast.hpp>

  #define START_TRACE()        \
  {                            \
    std::ofstream f_trace1496( \
    "trace_out.txt");          \
    f_trace1496.close();       \
  }                            \


  #define TRACE(x)             \
  {                            \
    std::ofstream f(           \
      "trace_out.txt",         \
      std::ios::app);          \
    f                          \
      << "TRACE \'"            \
      <<  std::string(#x )     \
      <<  "\' line "           \
      <<  (__LINE__)           \
      <<  " in file '"         \
      <<  __FILE__             \
      <<  "': '"               \
      <<  boost::lexical_cast< \
          std::string>(x)      \
      <<  "'"                  \
      << std::endl;            \
    f.close();                 \
    std::cout                  \
      << "TRACE \'"            \
      <<  std::string (#x)     \
      <<  "\' line "           \
      <<  (__LINE__)           \
      <<  " in file '"         \
      <<  __FILE__             \
      <<  "': '"               \
      <<  boost::lexical_cast< \
          std::string>(x)      \
      <<  "'"                  \
      << std::endl;            \
  }                            \

  //File-only trace
  #define FTRACE(x)            \
  {                            \
    std::ofstream f(           \
      "trace_out.txt",         \
      std::ios::app);          \
    f                          \
      << "TRACE \'"            \
      <<  std::string(#x )     \
      <<  "\' line "           \
      <<  (__LINE__)           \
      <<  " in file '"         \
      <<  __FILE__             \
      <<  "': '"               \
      <<  boost::lexical_cast< \
          std::string>(x)      \
      <<  "'"                  \
      << std::endl;            \
    f.close();                 \
  }                            \

  #define TRACE_FUNC()      \
  {                         \
    std::ofstream f(        \
      "trace_out.txt",      \
      std::ios::app);       \
    f                       \
      << "TRACE_FUNC "      \
      <<  (__func__)        \
      <<  " , "             \
      <<  (__LINE__)        \
      <<  " , "             \
      <<  __FILE__          \
      << std::endl;         \
    f.close();              \
    std::cout               \
      << "TRACE_FUNC "      \
      <<  (__func__)        \
      <<  " , "             \
      <<  (__LINE__)        \
      <<  " , "             \
      <<  __FILE__          \
      << std::endl;         \
  }                         \

#endif

#endif // TRACE_H
