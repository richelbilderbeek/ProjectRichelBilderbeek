exists (../../Libraries/ConsoleApplication.pri) {
  include(../../ConsoleApplication.pri)
}
!exists (../../Libraries/GeneralConsole.pri) {
  QT       += core gui
  greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
  TEMPLATE = app
  SOURCES += main.cpp
  QMAKE_CXXFLAGS += -Wall -Wextra -Werror
}


exists (../../Libraries/Qwt.pri) {
  include(../../Libraries/Qwt.pri)
}
!exists (../../Libraries/Qwt.pri) {
  INCLUDEPATH+= ../../Libraries/qwt-6.1/src
  LIBS+= -L../../Libraries/qwt-6.1/lib

  CONFIG(release, debug|release) {
    message(Windows: Qwt: Linking to qwt)
    LIBS += -lqwt
  }

  CONFIG(debug, debug|release) {
    message(Windows: Qwt: Linking to qwtd)
    LIBS += -lqwtd
  }
}


