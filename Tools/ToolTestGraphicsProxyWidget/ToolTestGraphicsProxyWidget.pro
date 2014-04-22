QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


SOURCES += \
    tooltestgraphicsproxywidgetmaindialog.cpp \
    qttestgraphicsproxywidget.cpp \
    qttestgraphicsproxyitem.cpp \
    somedialog.cpp \
    qtmain.cpp

HEADERS  += tooltestgraphicsproxywidgetmaindialog.h \
    qttestgraphicsproxywidget.h \
    qttestgraphicsproxyitem.h \
    somedialog.h

FORMS    += tooltestgraphicsproxywidgetmaindialog.ui \
    somedialog.ui

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
