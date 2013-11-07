QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TEMPLATE = app


SOURCES += main.cpp\
        dialoggame.cpp \
    player.cpp \
    worldtype.cpp

HEADERS  += dialoggame.h \
    player.h \
    worldtype.h

FORMS    += dialoggame.ui

RESOURCES += \
    GameTronCollection.qrc
