QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppEncranger \
    ../../Classes/CppLoopReader \
    ../../Classes/CppTrace \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig

SOURCES += wtmain.cpp \
    toolencrangermaindialog.cpp \
    toolencrangermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppEncranger/encranger.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    wttoolencrangermaindialog.cpp \
    wttoolencrangermenudialog.cpp

HEADERS  += \
    toolencrangermaindialog.h \
    toolencrangermenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppLoopReader/loopreader.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppTrace/trace.h \
    wttoolencrangermaindialog.h \
    wttoolencrangermenudialog.h

RESOURCES += \
    ToolMultiEncranger.qrc

LIBS += -lwt -lwthttp -lboost_program_options -lboost_signals -lboost_system -lboost_filesystem


QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++
unix {
  QMAKE_CXXFLAGS += -Werror
}

OTHER_FILES += \
    ../../Classes/CppTrace/Licence.txt
