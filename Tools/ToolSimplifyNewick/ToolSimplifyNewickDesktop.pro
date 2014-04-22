QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppFuzzy_equal_to \
  ../../Classes/CppNewick \
  ../../Classes/CppNewickVector \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtHideAndShowDialog \
  ../../Classes/CppTrace \
  ../../Libraries/bigint-2010.04.30

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp \
    ../../Classes/CppNewickVector/newickvector.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    main.cpp \
    qttoolsimplifynewickmaindialog.cpp \
    qttoolsimplifynewickmenudialog.cpp \
    toolsimplifynewickmaindialog.cpp \
    toolsimplifynewickmenudialog.cpp

HEADERS += \ 
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppNewickVector/newickvector.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qttoolsimplifynewickmaindialog.h \
    qttoolsimplifynewickmenudialog.h \
    toolsimplifynewickmaindialog.h \
    toolsimplifynewickmenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttoolsimplifynewickmaindialog.ui \
    qttoolsimplifynewickmenudialog.ui

RESOURCES += \
    ToolSimplifyNewick.qrc

OTHER_FILES += \
    ../../Classes/CppFuzzy_equal_to/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Big integer
#
#
INCLUDEPATH += \
    ../../Libraries/bigint-2010.04.30

HEADERS += \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.hh \
    ../../Libraries/bigint-2010.04.30/BigInteger.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerLibrary.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.hh \
    ../../Libraries/bigint-2010.04.30/NumberlikeArray.hh

SOURCES += \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
