win32 {
  #Add the line below when cross-compiling
  CONFIG += static
}

QT += core gui
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp \
    ../../Classes/CppCodeToHtml/codetohtml.cpp \
    ../../Classes/CppCodeToHtml/codetohtmldialog.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlheader.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlversion.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    codetohtmlmenudialog.cpp \
    qtcodetohtmlmaindialog.cpp \
    qtcodetohtmlmenudialog.cpp \
    qtmain.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.h \
    ../../Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h \
    ../../Classes/CppCodeToHtml/codetohtmldialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Classes/CppCodeToHtml/codetohtmlheader.h \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlversion.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    codetohtmlmenudialog.h \
    qtcodetohtmlmaindialog.h \
    qtcodetohtmlmenudialog.h \
    ../../Classes/CppQrcFile/qrcfile.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtcodetohtmlmaindialog.ui \
    qtcodetohtmlmenudialog.ui

RESOURCES += \
    ToolCodeToHtml.qrc

OTHER_FILES += \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    crosscompiletowindows.sh \
    zip.sh


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
  message("Boost build for Lubuntu")
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
    message("Boost 1.53.0 build for native Windows")
    INCLUDEPATH+=E:/boost_1_50_0

    LIBS+=\
      -LE:/boost_1_50_0/stage/lib\
      -lboost_system-mgw44-mt-1_50\
      -lboost_filesystem-mgw44-mt-1_50\
      -lboost_regex-mgw44-mt-1_50
  }


  static {
    #Boost libraries
    message("Static Boost 1.53.0 build for crosscompiling from Lubuntu to Windows")
    INCLUDEPATH += \
      ../../Libraries/boost_1_53_0

    #Prevent the following error:
    #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp: In function 'boost::program_options::parsed_options boost::program_options::parse_environment(const boost::program_options::options_description&, const boost::function1<std::basic_string<char>, std::basic_string<char> >&)':
    #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp:194:36: error: 'environ' was not declared in this scope
    DEFINES += __COMO_VERSION__


    #Boost.Data_time
    #HEADERS += \
    #  ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_names.hpp
    #SOURCES += \
    #  ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_weekday.cpp \
    #  ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/gregorian_types.cpp \
    #  ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_month.cpp \
    #  ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/date_generators.cpp

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
    # ../../Libraries/boost_1_53_0/libs/program_options/src/cmdline.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/config_file.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/convert.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/options_description.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/positional_options.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/split.cpp \
    # #../../Libraries/boost_1_53_0/libs/program_options/src/utf8_codecvt_facet.cpp \ #Comment, keep filesystem/src/utf8_codecvt_facet.cpp
    # ../../Libraries/boost_1_53_0/libs/program_options/src/value_semantic.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/variables_map.cpp \
    # ../../Libraries/boost_1_53_0/libs/program_options/src/winmain.cpp

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
