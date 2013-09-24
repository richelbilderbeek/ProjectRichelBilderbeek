QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppBinaryNewickVector \
  ../../Classes/CppFuzzy_equal_to \
  ../../Classes/CppNewick \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtHideAndShowDialog \
  ../../Classes/CppSortedBinaryNewickVector \
  ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qttestbinarynewickvectormaindialog.cpp \
    qtmain.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppNewick/newickstorage.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    qttestbinarynewickvectormaindialog.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h
FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestbinarynewickvectormaindialog.ui

RESOURCES += \
    ToolTestBinaryNewickVector.qrc


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
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}

unix : LIBS += -lboost_regex

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

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppFuzzy_equal_to/Licence.txt

