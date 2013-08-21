TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}

SOURCES += main.cpp

