win32 {
  # Windows only
  message("Web application, built for Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra
}

macx {
  # Mac only
  message("Web application, built for Mac")
  QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
  CONFIG +=c++11
}

unix:!macx{
  # Linux only
  message("Web application, built for Linux")
  greaterThan(QT_MAJOR_VERSION, 4): QT += svg sql printsupport
  #Cannot use -Weffc++ nor -Werror with Wt
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra
}

cross_compile {
  # Crosscompile only
  message("Web application, cross-compiling from Linux to Windows")
  QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
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

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}
