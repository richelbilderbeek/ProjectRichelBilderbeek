QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppLed \
    ../../Classes/CppRainbow \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtGroupWidget

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.cpp \
    wttestgroupwidgetmenudialog.cpp \
    wttestgroupwidgetmaindialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    testgroupwidgetmenudialog.cpp \
    ../../Classes/CppRainbow/rainbow.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.h \
    wttestgroupwidgetmenudialog.h \
    wttestgroupwidgetmaindialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    testgroupwidgetmenudialog.h \
    ../../Classes/CppRainbow/rainbow.h

RESOURCES += \
    ToolTestGroupWidget.qrc
