TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += \
    ../../Classes/CppIrcBot

SOURCES += \
    main.cpp \
    ../../Classes/CppIrcBot/messagehandle.cpp \
    ../../Classes/CppIrcBot/ircbot.cpp

HEADERS += \
    ../../Classes/CppIrcBot/messagehandle.h \
    ../../Classes/CppIrcBot/ircbot.h

