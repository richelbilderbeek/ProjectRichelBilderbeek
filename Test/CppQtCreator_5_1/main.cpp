#include "qtdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtDialog w;
  w.show();
  return a.exec();
}

/*


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

  #Boost libraries
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  #Prevent the following error:
  #../../Libraries/boost_1_54_0/libs/program_options/src/parsers.cpp: In function 'boost::program_options::parsed_options boost::program_options::parse_environment(const boost::program_options::options_description&, const boost::function1<std::basic_string<char>, std::basic_string<char> >&)':
  #../../Libraries/boost_1_54_0/libs/program_options/src/parsers.cpp:194:36: error: 'environ' was not declared in this scope
  #DEFINES += __COMO_VERSION__


  #Boost.Data_time
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/greg_names.hpp
  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/greg_weekday.cpp \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/gregorian_types.cpp \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/greg_month.cpp \
    ../../Libraries/boost_1_54_0/libs/date_time/src/gregorian/date_generators.cpp

  #Boost.Filesystem
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/windows_file_codecvt.hpp
  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/codecvt_error_category.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/operations.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/path.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/path_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/portability.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/unique_path.cpp \
    ../../Libraries/boost_1_54_0/libs/filesystem/src/utf8_codecvt_facet.cpp \ #Keep, comment program_options/src/utf8_codecvt_facet.cpp
    ../../Libraries/boost_1_54_0/libs/filesystem/src/windows_file_codecvt.cpp

  #Boost.Program_options
  #
  #This lib does not seem to work well together with Boost.Filesystem
  #when compiled from source like this
  #
  #SOURCES += \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/cmdline.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/config_file.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/convert.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/options_description.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/parsers.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/positional_options.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/split.cpp \
  #  #../../Libraries/boost_1_54_0/libs/program_options/src/utf8_codecvt_facet.cpp \ #Comment, keep filesystem/src/utf8_codecvt_facet.cpp
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/value_semantic.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/variables_map.cpp \
  #  ../../Libraries/boost_1_54_0/libs/program_options/src/winmain.cpp

  #Boost.Regex
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/regex/src/internals.hpp

  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/regex/src/winstances.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/wide_posix_api.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/wc_regex_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/w32_regex_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/usinstances.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/static_mutex.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex_traits_defaults.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex_raw_buffer.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex_debug.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/regex.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/posix_api.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/instances.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/icu.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/fileiter.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/c_regex_traits.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/cregex.cpp \
    ../../Libraries/boost_1_54_0/libs/regex/src/cpp_regex_traits.cpp

  #Boost.System
  HEADERS += \
    ../../Libraries/boost_1_54_0/libs/system/src/local_free_on_destruction.hpp
  SOURCES += \
    ../../Libraries/boost_1_54_0/libs/system/src/error_code.cpp
}



*/
