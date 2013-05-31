#-------------------------------------------------
#
# Project created by QtCreator 2010-08-19T15:10:48
#
#-------------------------------------------------
QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
#Use C++0x standard
#QMAKE_CXXFLAGS += -std=c++0x
#Use 64 bit
#QMAKE_CXXFLAGS += -m64

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppBinaryNewickVector \
  ../../Classes/CppFuzzy_equal_to \
  ../../Classes/CppNewick \
  ../../Classes/CppTrace \
  ../../Classes/CppTwoDigitNewick \
  ../../Libraries/bigint-2010.04.30

win32:INCLUDEPATH+=C:/QtSDK/Libraries/boost/boost_1_47_0

TARGET = TestTwoDigitNewickDesktop

#Libraries
unix:LIBS += -lboost_regex
#Using BigInt library by including its source
TEMPLATE = app
SOURCES += \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.cpp \
    ../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc \
    main.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp
HEADERS += \
    ../../Classes/CppAssert/assert.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h

