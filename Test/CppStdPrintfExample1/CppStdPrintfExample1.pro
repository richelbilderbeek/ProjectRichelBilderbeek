exists(../../ConsoleApplication.pri) {
  include(../../ConsoleApplication.pri)
}
!exists(../../ConsoleApplication.pri) {
  QT += core
  QT += gui
  CONFIG   += console
  CONFIG   -= app_bundle
  TEMPLATE = app
  CONFIG(release, debug|release) {
    DEFINES += NDEBUG NTRACE_BILDERBIKKEL
  }
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
  unix {
    QMAKE_CXXFLAGS += -Werror
  }
}

SOURCES += main.cpp
