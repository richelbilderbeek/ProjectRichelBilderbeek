QT += core
QT -= gui
SOURCES += \
    beerwanter.cpp \
    mainWt.cpp \
    beerwanterwtwidget.cpp
HEADERS  += \
    beerwanter.h \
    beerwanterwtwidget.h \
    myassert.h


CONFIG   += console
CONFIG   += qt
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

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}

#
#
# Wt
#
#

unix {
  LIBS += -lwt -lwthttp
}
