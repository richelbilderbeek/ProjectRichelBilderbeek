QT       += core gui
LIBS += -lwt -lwthttp -lboost_program_options
TEMPLATE = app
#Use C++0x standard
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -DNDEBUG
DEFINES += USE_WT_LIBRARY
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppBinaryNewickVector \
  ../../Classes/CppEncranger \
  ../../Classes/CppLoopReader \
  ../../Classes/CppNewick \
  ../../Classes/CppNewickVector \
  ../../Classes/CppTrace \
  ../../Classes/CppTwoDigitNewick \
  ../../Classes/CppWtAboutDialog \
  ../../Libraries/bigint-2010.04.30
#Message showing what the application is thinking
unix: CONFIG(debug  ,debug|release):message("Building Ubuntu debug")
unix: CONFIG(release,debug|release):message("Building Ubuntu release")
win32:CONFIG(debug  ,debug|release):message("Building Windows debug")
win32:CONFIG(release,debug|release):message("Building Windows release")
#Application name
#Debug flag for keeping/removing assert
CONFIG(release,debug|release):DEFINES += NDEBUG
#Libraries
win32: LIBS +=C:/Qt/2010.02.1/qt/lib/libboost_regex.lib
unix:  LIBS += -lboost_regex

#Using BigInt library by including its source
SOURCES += wtmain.cpp \
    testnewickvectordialog.cpp \
  wttestnewickvectordialog.cpp \
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
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppEncranger/encranger.cpp
TEMPLATE = app
HEADERS += \
    testnewickvectordialog.h \
  wttestnewickvectordialog.h \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppNewick/newick.h \
  ../../Classes/CppNewickVector/newickvector.h \
  ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
  ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppLoopReader/loopreader.h
OTHER_FILES += \
    wt.css
