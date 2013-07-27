#-------------------------------------------------
#
# Project created by QtCreator 2010-08-19T15:10:48
#
#-------------------------------------------------
QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppBinaryNewickVector \
  ../../Classes/CppManyDigitNewick \
  ../../Classes/CppMultiVector \
  ../../Classes/CppNewick \
  ../../Classes/CppNewickVector \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppTrace \
  ../../Classes/CppTwoDigitNewick
#Debug flag for keeping/removing assert
CONFIG(release,debug|release):DEFINES += NDEBUG
DEFINES += DEBUG_SKIP_SAZ_AND_SAO
#Add the path of the BigInt library
INCLUDEPATH += ../../Libraries/bigint-2010.04.30
#Libraries
win32: LIBS +=C:/Qt/2010.02.1/qt/lib/libboost_regex.lib
unix : LIBS += -L/usr/local/lib -lboost_regex
#Using BigInt library by including its source
TEMPLATE = app
SOURCES += main.cpp \
    dialogtestmanydigitnewick.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewick.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
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
    ../../Classes/CppNewickVector/newickvector.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.cpp
HEADERS += \
    dialogtestmanydigitnewick.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.h \
    ../../Classes/CppManyDigitNewick/manydigitnewick.h \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.h \
    ../../Classes/CppMultiVector/multivector.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppNewickVector/newickvector.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.h
FORMS += \
    dialogtestmanydigitnewick.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
RESOURCES += \
    resources.qrc

OTHER_FILES += \
    ../../Classes/CppManyDigitNewick/manydigitnewickalgorithm.txt
