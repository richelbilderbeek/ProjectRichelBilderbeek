QT       += core gui
TARGET = ToolSimMysteryMachineDesktop
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppLed \
    ../../Classes/CppLedWidget \
    ../../Classes/CppMysteryMachine \
    ../../Classes/CppMysteryMachineWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtDialWidget \
    ../../Classes/CppQtLedWidget \
    ../../Classes/CppQtMysteryMachineWidget \
    ../../Classes/CppQtToggleButtonWidget \
    ../../Classes/CppRectangle \
    ../../Classes/CppToggleButton \
    ../../Classes/CppToggleButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget

SOURCES += qtmain.cpp \
    qtsimmysterymachinemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppMysteryMachine/mysterymachine.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtLedDisplayWidget/qtleddisplaywidget.cpp \
    simmysterymachinemenudialog.cpp \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    qtsimmysterymachinemaindialog.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.cpp \
    ../../Classes/CppQtLedWidget/qtledwidget.cpp \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppQtDialWidget/qtdialwidget.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    qtsimmysterymachineinstructionsdialog.cpp \
    qtsimmysterymachinerealmachinedialog.cpp

HEADERS  += \
    qtsimmysterymachinemenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppMysteryMachine/mysterymachine.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtLedDisplayWidget/qtleddisplaywidget.h \
    simmysterymachinemenudialog.h \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    qtsimmysterymachinemaindialog.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.h \
    ../../Classes/CppQtLedWidget/qtledwidget.h \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppQtDialWidget/qtdialwidget.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    qtsimmysterymachineinstructionsdialog.h \
    qtsimmysterymachinerealmachinedialog.h

FORMS    += \
    qtsimmysterymachinemenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtsimmysterymachinemaindialog.ui \
    qtsimmysterymachineinstructionsdialog.ui \
    qtsimmysterymachinerealmachinedialog.ui

RESOURCES += \
    ToolSimMysteryMachine.qrc
