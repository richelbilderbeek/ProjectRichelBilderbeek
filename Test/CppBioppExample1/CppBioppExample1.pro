#include(../../ConsoleApplicationNoWeffcpp.pri)
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

include(../../Libraries/BoostAll.pri)
include(../../Libraries/Biopp.pri)

#LIBS += -lgsl
#LIBS += -lgslcblas
#LIBS += -lz

SOURCES += main.cpp
