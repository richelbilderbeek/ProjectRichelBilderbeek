QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


SOURCES += \
    tooltestgravitywidgetmaindialog.cpp \
    qtgravitywidgetitem.cpp \
    qtgravitywidget.cpp \
    qtmain.cpp

HEADERS  += tooltestgravitywidgetmaindialog.h \
    qtgravitywidgetitem.h \
    qtgravitywidget.h

FORMS    += tooltestgravitywidgetmaindialog.ui

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
