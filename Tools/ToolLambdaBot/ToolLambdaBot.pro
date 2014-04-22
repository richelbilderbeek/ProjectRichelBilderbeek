TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++ -Werror

INCLUDEPATH += \
    ../../Classes/CppIrcBot

SOURCES += \
    main.cpp \
    ../../Classes/CppIrcBot/ircbot.cpp

HEADERS += \
    ../../Classes/CppIrcBot/ircbot.h

