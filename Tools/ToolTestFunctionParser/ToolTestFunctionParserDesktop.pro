QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp \
    qttestfunctionparsermaindialog.cpp \
    qttestfunctionparsermenudialog.cpp \
    testfunctionparsermenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Libraries/fparser4.4.3/fparser.hh \
    qttestfunctionparsermaindialog.h \
    qttestfunctionparsermenudialog.h \
    testfunctionparsermenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestfunctionparsermaindialog.ui \
    qttestfunctionparsermenudialog.ui

RESOURCES += \
    ToolTestFunctionParser.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt


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
  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
  }

  #Allow the crosscompiler to emit warnings without terminating
  QMAKE_CXXFLAGS += -std=c++11 #-Werror

  #Prevents error:
  #/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
  DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED
}

#
#
# Warp's function parser
#
#
unix {
  INCLUDEPATH += \
    ../../Libraries/fparser4.5.1

  HEADERS += \
    ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
    ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
    ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
    ../../Libraries/fparser4.5.1/fparser.hh \
    ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
    ../../Libraries/fparser4.5.1/fpconfig.hh

  SOURCES += \
    ../../Libraries/fparser4.5.1/fparser.cc \
    ../../Libraries/fparser4.5.1/fpoptimizer.cc


  OTHER_FILES += \
    ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
    ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/fparser4.5.1

  HEADERS += \
    ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
    ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
    ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
    ../../Libraries/fparser4.5.1/fparser.hh \
    ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
    ../../Libraries/fparser4.5.1/fpconfig.hh

  SOURCES += \
    ../../Libraries/fparser4.5.1/fparser.cc \
    ../../Libraries/fparser4.5.1/fpoptimizer.cc


  OTHER_FILES += \
    ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
    ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
}
