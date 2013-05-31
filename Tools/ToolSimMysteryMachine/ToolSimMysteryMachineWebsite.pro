QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options -lboost_signals -lboost_regex -lboost_system -lboost_filesystem -lboost_program_options
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppLed \
    ../../Classes/CppLedWidget \
    ../../Classes/CppMysteryMachine \
    ../../Classes/CppMysteryMachineWidget \
    ../../Classes/CppRectangle \
    ../../Classes/CppToggleButton \
    ../../Classes/CppToggleButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtDialWidget \
    ../../Classes/CppWtLedWidget \
    ../../Classes/CppWtLedWidget \
    ../../Classes/CppWtMysteryMachineWidget \
    ../../Classes/CppWtToggleButtonWidget

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppMysteryMachine/mysterymachine.cpp \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppWtLedWidget/wtledwidget.cpp \
    ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.cpp \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp \
    simmysterymachinemenudialog.cpp \
    wtsimmysterymachinemaindialog.cpp \
    wtsimmysterymachinemenudialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppMysteryMachine/mysterymachine.h \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppWtLedWidget/wtledwidget.h \
    ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.h \
    ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.h \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h \
    simmysterymachinemenudialog.h \
    wtsimmysterymachinemaindialog.h \
    wtsimmysterymachinemenudialog.h

RESOURCES += \
    ToolSimMysteryMachine.qrc
