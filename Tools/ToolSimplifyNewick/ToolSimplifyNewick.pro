CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x
#Configure difference in debug and release version
CONFIG(debug, debug|release) {
  message(Building debug version)

} else {
  DEFINES += NDEBUG
  message(Building release version)
}
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppNewick \
  ../../Classes/CppNewickVector \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppTrace \
  ../../Libraries/bigint-2010.04.30
LIBS += -lboost_regex
TEMPLATE = app
SOURCES += main.cpp \
    dialogsimplifynewick.cpp \
#    ../ToolTestNewickVector/newickvector.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../Classes/CppNewickVector/newickvector.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp
HEADERS += \ 
    dialogsimplifynewick.h \
#    ../ToolTestNewickVector/newickvector.h \
    ../../Classes/CppNewick/newick.h \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerLibrary.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.hh \
    ../../Libraries/bigint-2010.04.30/BigInteger.hh \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppNewickVector/newickvector.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h
FORMS += \
    dialogsimplifynewick.ui \
    dialogabout.ui \
    dialogwhatsnew.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
RESOURCES += \
    resources.qrc
