
win32 {
  # Windows only
  message("Desktop application, built for Windows")
  greaterThan(QT_MAJOR_VERSION, 4): QT += svg sql printsupport #webkit
  QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++
}

macx {
  # Mac only
  message("Desktop application, built for Mac")
  QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
  CONFIG +=c++11
}

unix:!macx {
  # Linux only
  message("Desktop application, built for Linux")
  greaterThan(QT_MAJOR_VERSION, 4): QT += svg sql printsupport
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++ -Werror
}

cross_compile {
  # Crosscompile only
  message("Desktop application, built for cross-compiling from Linux to Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
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

