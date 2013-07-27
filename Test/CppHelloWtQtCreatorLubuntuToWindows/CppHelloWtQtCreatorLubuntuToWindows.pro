QT       += core
QT       -= gui

!win32 {
  error(Must be a Win32 environment)
}
win32 {
  !cross_compile {
    error(Must be using crosscompiler)
  }
  cross_compile {
    LIBS += -L../../Libraries/mxe/usr/i686-pc-mingw32/lib
    LIBS += -lwt -lwthttp -lboost_signals
  }
}
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
