QT += core gui
LIBS += -lwt -lwthttp -lboost_signals -lboost_regex -lboost_program_options -lboost_system -lboost_filesystem
QMAKE_CXXFLAGS += -DNDEBUG -std=c++0x -Wall -Wextra
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppRandomCode \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppRandomCode/randomcode.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    randomcodemenudialog.cpp \
    wtrandomcodegeneratedialog.cpp \
    wtrandomcodemenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppRandomCode/randomcode.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    randomcodemenudialog.h \
    wtrandomcodegeneratedialog.h \
    wtrandomcodemenudialog.h

RESOURCES += \
    ToolRandomCode.qrc
