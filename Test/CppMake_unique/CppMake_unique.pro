unix:!macx{
  # Linux only
  message("Console application, built for Linux")
  QMAKE_CXXFLAGS += -Werror
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
}

QT += core
QT += gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app


include(../../Libraries/Boost.pri)

SOURCES += main.cpp
