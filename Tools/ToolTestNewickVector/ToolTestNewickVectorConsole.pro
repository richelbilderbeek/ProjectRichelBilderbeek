QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppBinaryNewickVector \
  ../../Classes/CppFuzzy_equal_to \
  ../../Classes/CppNewick \
  ../../Classes/CppNewickVector \
  ../../Classes/CppTrace \
  ../../Classes/CppTwoDigitNewick \
  ../../Libraries/bigint-2010.04.30

#Libraries
#win32: LIBS +=C:/Qt/2010.02.1/qt/lib/libboost_regex.lib
unix:LIBS += -lboost_regex

win32:INCLUDEPATH+=C:/QtSDK/Libraries/boost/boost_1_47_0

#Using BigInt library by including its source
SOURCES += \
  testnewickvectordialog.cpp \
  ../../Libraries/bigint-2010.04.30/BigInteger.cc \
  ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
  ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
  ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
  ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppNewick/newick.cpp \
  ../../Classes/CppNewickVector/newickvector.cpp \
  ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
  ../../Classes/CppTwoDigitNewick/twodigitnewicks.cpp \
  ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.cpp \
  ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.cpp \
  ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.cpp \
  ../../Classes/CppTwoDigitNewick/twodigitnewick.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp \
    main.cpp
TEMPLATE = app
HEADERS += \
  testnewickvectordialog.h \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppNewick/newick.h \
  ../../Classes/CppNewickVector/newickvector.h \
  ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h

FORMS += \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.ui







