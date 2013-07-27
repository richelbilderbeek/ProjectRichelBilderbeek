#-------------------------------------------------
#
# Project created by QtCreator 2010-08-19T15:10:48
#
#-------------------------------------------------
QT       += core
CONFIG   += console
CONFIG   -= app_bundle
#Disallow release version
#CONFIG   += debug
#CONFIG   -= release
#Under Windows, under release mode, add this dumb config,
#otherwise, it will still be in debug mode (beats me why)
CONFIG -= debug
#Message showing what the application is thinking
unix: CONFIG(debug  ,debug|release):message("Building Ubuntu debug")
unix: CONFIG(release,debug|release):message("Building Ubuntu release: SHOULD NOT HAPPEN")
win32:CONFIG(debug  ,debug|release):message("Building Windows debug")
win32:CONFIG(release,debug|release):message("Building Windows release: SHOULD NOT HAPPEN")
#Application name
#Debug flag for keeping/removing assert
CONFIG(release,debug|release):DEFINES += NDEBUG
#Add the path of the BigInt library and BinaryNewickVector
INCLUDEPATH +=                         \
  ../../../Classes/CppBinaryNewickVector  \
  ../../../Classes/CppNewick  \
  ../../../Classes/CppStopwatch \
  ../../../Libraries/bigint-2010.04.30
#Libraries
win32:LIBS += C:/Qt/2010.02.1/qt/lib/libboost_filesystem.lib
unix:LIBS += -lboost_filesystem
#Using BigInt library by including its source
SOURCES += \
    dialogrampaltest.cpp \
    ProjectRampalTest.cpp \
    test.cpp \
    ../../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc \
    ../../../Classes/CppNewick/newick.cpp
HEADERS += \
    test.h \
    dialogrampaltest.h \
    ../../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../../Classes/CppStopwatch/stopwatch.h \
    ../../../Classes/CppNewick/newick.h
FORMS += \
    dialogrampaltest.ui
RESOURCES += \
    resources.qrc
