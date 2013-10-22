TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

unix {
  QMAKE_CXXFLAGS += -Werror
}
SOURCES += main.cpp

