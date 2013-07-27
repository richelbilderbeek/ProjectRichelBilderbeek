QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppLed \
    ../../Classes/CppLedWidget \
    ../../Classes/CppRainbow \
    ../../Classes/CppRectangle \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtLedWidget \
    ../../Classes/CppWtDialWidget \
    ../../Classes/CppWidget

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppWtLedWidget/wtledwidget.cpp \
    testledmenudialog.cpp \
    wttestledmaindialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    wttestledmenudialog.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppRainbow/rainbow.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppWtLedWidget/wtledwidget.h \
    testledmenudialog.h \
    wttestledmaindialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    wttestledmenudialog.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppRainbow/rainbow.h

RESOURCES += \
    ToolTestLed.qrc
