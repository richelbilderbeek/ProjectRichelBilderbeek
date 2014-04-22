win32 {
  # Windows only
  message("Desktop application, no effc++, built for Windows")
  greaterThan(QT_MAJOR_VERSION, 4): QT += svg
}

macx {
  # Mac only
  message("Desktop application, no effc++, built for Mac")
}

unix:!macx{
  # Linux only
  message("Desktop application, no effc++, built for Linux")
}

cross_compile {
  # Crosscompile only
  message("Desktop application, no effc++, cross-compiling from Linux to Windows")
  greaterThan(QT_MAJOR_VERSION, 4): QT += svg
}


QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra #-Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}
