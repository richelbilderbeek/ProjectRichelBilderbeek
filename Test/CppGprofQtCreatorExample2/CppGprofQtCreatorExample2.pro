QT       += core
QT       -= gui

#Use gprof for profiling in release mode, use for run-time speed optimization
QMAKE_CXXFLAGS += -pg
QMAKE_LFLAGS += -pg
#Use gprof for profiling in debug mode, okay for detecting memory leaks
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += main.cpp


#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra


unix {
  message(Unix)
  QMAKE_CXXFLAGS += -Werror
}
