include(../../ConsoleApplication.pri) #Or use the code below
include(../../Libraries/Boost.pri)


LIBS += -L../../Libraries/gmock-1.7.0/lib -lgmock
SOURCES += main.cpp

