QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
    qtmain.cpp \
    qttextpositionwidget.cpp \
    qttextpositionitem.cpp \
    qttooltesttextpositionwidgetdialog.cpp

HEADERS += \
    qttextpositionwidget.h \
    qttextpositionitem.h \
    qttooltesttextpositionwidgetdialog.h

FORMS += \
    qttooltesttextpositionwidgetdialog.ui

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
