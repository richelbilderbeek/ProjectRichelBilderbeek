TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
SOURCES += main.cpp

win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}

