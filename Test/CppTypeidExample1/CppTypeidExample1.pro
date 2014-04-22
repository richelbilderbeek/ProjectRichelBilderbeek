TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++
unix {
  QMAKE_CXXFLAGS += -Werror
}
