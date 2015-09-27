win32 {
  # Windows only
  message("Console application, built for Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra
}

macx {
  # Mac only
  message("Console application, built for Mac")
  QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
  CONFIG +=c++1y
}

unix:!macx{
  # Linux only
  message("Console application, built for Linux")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Werror
}

cross_compile {
  # Crosscompile only
  message("Console application, cross-compiling from Linux to Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra
}


# Go ahead and use Qt.Core: it is about as platform-independent as
# the STL and Boost
QT += core

# Go ahead and use Qt.Gui: it is about as platform-independent as
# the STL and Boost. It is needed for QImage
QT += gui

# Don't define widgets: it would defy the purpose of this console
# application to work non-GUI
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

