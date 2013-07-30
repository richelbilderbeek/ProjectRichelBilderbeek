QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
#Use the C++0x standard
QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppBinaryNewickVector \
  ../../Classes/CppNewick \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppSortedBinaryNewickVector \
  ../../Classes/CppTrace \
  ../../Libraries/bigint-2010.04.30
#Debug flag for keeping/removing assert
CONFIG(release,debug|release):DEFINES += NDEBUG
#Libraries
win32: LIBS += C:/Qt/2010.02.1/qt/lib/libboost_regex.lib
unix : LIBS += -lboost_regex
#Using BigInt library by including its source
SOURCES += \
    dialogtestbinarynewickvector.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.cpp \
    ../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc
TEMPLATE = app
SOURCES += main.cpp
HEADERS += \
    dialogtestbinarynewickvector.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppNewick/newickstorage.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.h
FORMS += \
    dialogtestbinarynewickvector.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
RESOURCES += \
    ToolTestBinaryNewickVector.qrc
