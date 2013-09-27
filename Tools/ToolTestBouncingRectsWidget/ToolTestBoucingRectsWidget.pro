QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
    qtbouncingrect.cpp \
    qtbouncingrectswidget.cpp \
    qtmain.cpp \
    qttooltestbouncingrectswidgetmaindialog.cpp

HEADERS  += \
    qtbouncingrect.h \
    qtbouncingrectswidget.h \
    qttooltestbouncingrectswidgetmaindialog.h

FORMS    += qttooltestbouncingrectswidgetmaindialog.ui

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
