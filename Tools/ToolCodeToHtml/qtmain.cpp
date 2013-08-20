//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <QApplication>
#include <iostream>
#include "codetohtml.h"
#include "qtcreatorprofile.h"
#include "qtcodetohtmlmenudialog.h"
#include "codetohtmldialog.h"
#include "trace.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //try
  {
    START_TRACE();
    #ifndef _WIN32
    assert(c2h::IsTidyInstalled() && "I really want to be sure that tidy is installed");
    #endif

    #ifndef NDEBUG
    c2h::Test();
    #endif

    QtCodeToHtmlMenuDialog w;
    w.show();
    return a.exec();
  }
  /*
  catch (std::exception& e)
  {
    std::cerr << "Exception thrown: " << e.what() << '\n';
    return 1;
  }
  */
}

/*

#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -Wall -Wextra

unix {
  message(Unix)
  #Strict error handling
  QMAKE_CXXFLAGS += -std=c++11 -Werror
}

win32 {
  !static {
    message(Native Windows)
    #Allow the crosscompiler to emit warnings without terminating
    QMAKE_CXXFLAGS += -std=c++0x #-Werror
  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
    #Allow the crosscompiler to emit warnings without terminating
    QMAKE_CXXFLAGS += -std=c++11 #-Werror
  }


  #Prevents error:
  #/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
  DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED
}

#
#
# Boost
#
#

unix {
  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {
  !static {
    #Native windows
    INCLUDEPATH+=E:/boost_1_50_0

    LIBS+=\
      -LE:/boost_1_50_0/stage/lib\
      -lboost_system-mgw44-mt-1_50\
      -lboost_filesystem-mgw44-mt-1_50\
      -lboost_regex-mgw44-mt-1_50
  }


  static {
    #Boost libraries
    INCLUDEPATH += \
      ../../Libraries/boost_1_53_0

    #Prevent the following error:
    #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp: In function 'boost::program_options::parsed_options boost::program_options::parse_environment(const boost::program_options::options_description&, const boost::function1<std::basic_string<char>, std::basic_string<char> >&)':
    #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp:194:36: error: 'environ' was not declared in this scope
    DEFINES += __COMO_VERSION__


    #Boost.Data_time
    HEADERS += \
      ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_names.hpp
    SOURCES += \
      ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_weekday.cpp \
      ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/gregorian_types.cpp \
      ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_month.cpp \
      ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/date_generators.cpp

    #Boost.Filesystem
    HEADERS += \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.hpp
    SOURCES += \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/codecvt_error_category.cpp \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/operations.cpp \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/path.cpp \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/path_traits.cpp \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/portability.cpp \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/unique_path.cpp \
      ../../Libraries/boost_1_53_0/libs/filesystem/src/utf8_codecvt_facet.cpp \ #Keep, comment program_options/src/utf8_codecvt_facet.cpp
      ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.cpp

    #Boost.Program_options
    #
    #This lib does not seem to work well together with Boost.Filesystem
    #when compiled from source like this
    #
    #SOURCES += \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/cmdline.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/config_file.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/convert.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/options_description.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/positional_options.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/split.cpp \
    #  #../../Libraries/boost_1_53_0/libs/program_options/src/utf8_codecvt_facet.cpp \ #Comment, keep filesystem/src/utf8_codecvt_facet.cpp
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/value_semantic.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/variables_map.cpp \
    #  ../../Libraries/boost_1_53_0/libs/program_options/src/winmain.cpp

    #Boost.Regex
    HEADERS += \
      ../../Libraries/boost_1_53_0/libs/regex/src/internals.hpp

    SOURCES += \
      ../../Libraries/boost_1_53_0/libs/regex/src/winstances.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/wide_posix_api.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/wc_regex_traits.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/w32_regex_traits.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/usinstances.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/static_mutex.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/regex_traits_defaults.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/regex_raw_buffer.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/regex_debug.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/regex.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/posix_api.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/instances.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/icu.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/fileiter.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/c_regex_traits.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/cregex.cpp \
      ../../Libraries/boost_1_53_0/libs/regex/src/cpp_regex_traits.cpp

    #Boost.System
    HEADERS += \
      ../../Libraries/boost_1_53_0/libs/system/src/local_free_on_destruction.hpp
    SOURCES += \
      ../../Libraries/boost_1_53_0/libs/system/src/error_code.cpp
  }
}

*/
