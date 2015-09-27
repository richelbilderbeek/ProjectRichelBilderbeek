include(../../ConsoleApplicationNoWeffcpp.pri)
include(../../Classes/CppGslLite/CppGslLite.pri)

SOURCES += main.cpp

DEFINES += GSL_ARRAY_VIEW_H GSL_STRING_VIEW_H

QMAKE_CXXFLAGS += -fpermissive
#QMAKE_CXXFLAGS += -fpedantic
