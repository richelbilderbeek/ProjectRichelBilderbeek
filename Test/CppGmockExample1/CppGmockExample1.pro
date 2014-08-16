include(../../ConsoleApplicationNoEffCpp.pri) #Google Test does not go well together with -weffc++
include(../../Libraries/Boost.pri)


INCLUDEPATH += ../../Libraries/gmock-1.7.0/include
INCLUDEPATH += ../../Libraries/gmock-1.7.0/gtest/include

LIBS += -L../../Libraries/gmock-1.7.0/lib -lgmock
LIBS += -L../../Libraries/gmock-1.7.0/gtest/lib -lgtest

SOURCES += main.cpp

