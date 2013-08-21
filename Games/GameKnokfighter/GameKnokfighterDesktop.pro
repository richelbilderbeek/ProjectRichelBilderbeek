QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
INCLUDEPATH += \
    ../../Classes/CppRainbow \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    qtknokfighterbackground.cpp \
    qtknokfightermaindialog.cpp \
    qtknokfighterplayer.cpp \
    ../../Classes/CppRainbow/rainbow.cpp
#    knokfighterplayer.cpp \
#    knokighterkey.cpp \
#    knokfighterkey.cpp
#    knokfighterplayerstate.cpp \
#   knokfighterattack.cbpp

HEADERS  += \
    qtknokfighterbackground.h \
    qtknokfightermaindialog.h \
    qtknokfighterplayer.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppRainbow/rainbow.h
#    knokfighterplayer.h \
#    knokighterkey.h \
#    knokfighterkey.h
#   knokfighterplayerstate.h \
#   knokfighterattack.h

RESOURCES += \
    GameKnokkfighter.qrc

OTHER_FILES += \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppRainbow/Licence.txt
