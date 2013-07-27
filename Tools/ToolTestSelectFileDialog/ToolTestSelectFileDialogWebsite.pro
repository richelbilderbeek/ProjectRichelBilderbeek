#-------------------------------------------------
#
# Project created by QtCreator 2011-07-01T12:01:36
#
#-------------------------------------------------
QT       += core
QT       -= gui
LIBS += \
  -lwt -lwthttp \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system \
  -lboost_filesystem

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCopy_if \
    ../../Classes/CppTrace \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtSelectFileDialog

SOURCES += \
    wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp \
    wttestselectfiledialogmenudialog.cpp \
    wttestselectfiledialogmaindialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.h \
    wttestselectfiledialogmenudialog.h \
    wttestselectfiledialogmaindialog.h \
    ../../Classes/CppCopy_if/copy_if.h \
    ../../Classes/CppTrace/trace.h

RESOURCES += \
    ToolTestSelectFileDialog.qrc
