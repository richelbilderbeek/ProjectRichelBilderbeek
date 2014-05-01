exists (../../ConsoleApplication.pri) {
  include(../../ConsoleApplication.pri)
}
!exists (../../ConsoleApplication.pri) {
  QT += core
  QT += gui
  CONFIG   += console
  CONFIG   -= app_bundle
  TEMPLATE = app
  CONFIG(release, debug|release) {
    DEFINES += NDEBUG NTRACE_BILDERBIKKEL
  }

  QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

  unix {
    QMAKE_CXXFLAGS += -Werror
  }
}

exists(../../Libraries/Boost.pri) {
  include(../../Libraries/Boost.pri)
}
!exists(../../Libraries/Boost.pri) {
  win32 {
    INCLUDEPATH += \
      ../../Libraries/boost_1_54_0
  }
}

SOURCES += main.cpp
