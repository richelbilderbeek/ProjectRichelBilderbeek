#-------------------------------------------------
#
# Project created by QtCreator 2010-07-24T16:04:35
#
#-------------------------------------------------
QT += core gui
TARGET = ToolCodeToHtml
TEMPLATE = app

#QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lwt -lwthttp

SOURCES += \
    SimpleChatWidget.C \
    SimpleChatServer.C \
    simpleChat.C \
    PopupChatWidget.C
HEADERS += \
    SimpleChatWidget.h \
    SimpleChatServer.h \
    PopupChatWidget.h
