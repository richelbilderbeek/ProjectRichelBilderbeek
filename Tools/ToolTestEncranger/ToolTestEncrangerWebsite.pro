#-------------------------------------------------
#
# Project created by QtCreator 2011-03-06T10:58:35
#
#-------------------------------------------------
QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppEncranger \
    ../../Classes/CppLoopReader \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig

SOURCES += wtmain.cpp \
    testencrangerdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppEncranger/encranger.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    wttestencrangermaindialog.cpp \
    wttestencrangermenudialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp

HEADERS  += \
    testencrangerdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppLoopReader/loopreader.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    wttestencrangermaindialog.h \
    wttestencrangermenudialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h

RESOURCES += \
    ToolTestEncranger.qrc
