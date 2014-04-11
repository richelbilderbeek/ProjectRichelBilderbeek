exists(../../DesktopApplication.pri) {
  include(../../DesktopApplication.pri)
}
!exists(../../DesktopApplication.pri) {
  QT       += core gui
  greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

  win32 {
    greaterThan(QT_MAJOR_VERSION, 4): QT += svg
  }

  TEMPLATE = app

  CONFIG(debug, debug|release) {
    message(Debug mode)
  }

  CONFIG(release, debug|release) {
    message(Release mode)
    DEFINES += NDEBUG NTRACE_BILDERBIKKEL
  }

  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++

  unix {
    QMAKE_CXXFLAGS += -Werror
  }
}

exists(../../Libraries/Boost.pri) {
  include(../../Libraries/Boost.pri)
}
!exists(../../Libraries/Boost.pri) {
  INCLUDEPATH += \
    ../../Libraries/boost_1_55_0
}

SOURCES += \
    qtmain.cpp \
    qtwidget.cpp \
    qttextitem.cpp

HEADERS += \
    qtwidget.h \
    qttextitem.h
