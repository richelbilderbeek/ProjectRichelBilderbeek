QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app


SOURCES += main.cpp\
    dialogabout.cpp \
    dialogwhatsnew.cpp \
    dialogmain.cpp

HEADERS  += \
    dialogabout.h \
    dialogwhatsnew.h \
    dialogmain.h

FORMS    += dialog.ui \
    dialogabout.ui \
    dialogwhatsnew.ui \
    dialogmain.ui

RESOURCES += \
    ToolUbuntuOneWatcher.qrc
