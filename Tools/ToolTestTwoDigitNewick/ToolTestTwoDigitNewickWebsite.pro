QT       += core gui

CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppBinaryNewickVector \
  ../../Classes/CppEncranger \
  ../../Classes/CppFuzzy_equal_to \
  ../../Classes/CppLoopReader \
  ../../Classes/CppNewick \
  ../../Classes/CppTrace \
  ../../Classes/CppTwoDigitNewick \
  ../../Classes/CppWtAboutDialog \
  ../../Libraries/bigint-2010.04.30


CONFIG(release,debug|release): DEFINES += NDEBUG

LIBS += -lboost_regex -lwt -lwthttp

TEMPLATE = app

SOURCES += wtmain.cpp \
    wttesttwodigitnewickdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
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
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppEncranger/encranger.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp

HEADERS += \
    wttesttwodigitnewickdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAssert/assert.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h

RESOURCES += \
    ToolTestTwoDigitNewick.qrc
OTHER_FILES += \
    wt.css

# References
# [1] http://www.richelbilderbeek.nl/CppCompileErrorCc1plusInternalCompilerErrorSegmentationFault.htm
