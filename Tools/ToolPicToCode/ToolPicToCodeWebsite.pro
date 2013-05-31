#-------------------------------------------------
#
# Project created by QtCreator 2010-10-10T15:04:27
#
#-------------------------------------------------
QT       += core gui
TARGET = ToolPicToCodeWebsite
LIBS += -lwt -lwthttp
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtSprites \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig
SOURCES += wtmain.cpp\
    wtpictocodemaindialog.cpp \
    pictocodemaindialog.cpp \
    pictocodemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    wtpictocodemenudialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp
HEADERS  += \
    pictocodemaindialog.h \
    pictocodemenudialog.h \
    wtpictocodemaindialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    wtpictocodemenudialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h

RESOURCES += \
    ToolPicToCode.qrc
