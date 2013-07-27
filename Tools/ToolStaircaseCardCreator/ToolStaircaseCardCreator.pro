QT       += core gui

TEMPLATE = app


SOURCES += main.cpp\
        dialogmenu.cpp \
    dialogwhatsnew.cpp \
    dialogabout.cpp \
    dialogcreate.cpp \
    staircasecard.cpp \
    staircasecardwidget.cpp

HEADERS  += dialogmenu.h \
    dialogwhatsnew.h \
    dialogabout.h \
    dialogcreate.h \
    staircasecard.h \
    staircasecardwidget.h

FORMS    += dialogmenu.ui \
    dialogwhatsnew.ui \
    dialogabout.ui \
    dialogcreate.ui

RESOURCES += \
    resources.qrc
