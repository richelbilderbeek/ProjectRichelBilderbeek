QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++ -Werror

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
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppMysteryMachine/mysterymachine.cpp \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtDialWidget/qtdialwidget.cpp \
    ../../Classes/CppQtLedDisplayWidget/qtleddisplaywidget.cpp \
    ../../Classes/CppQtLedWidget/qtledwidget.cpp \
    ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.cpp \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    qtsimmysterymachineinstructionsdialog.cpp \
    qtsimmysterymachinemaindialog.cpp \
    qtsimmysterymachinemenudialog.cpp \
    qtsimmysterymachinerealmachinedialog.cpp \
    simmysterymachinemenudialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppMysteryMachine/mysterymachine.h \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtDialWidget/qtdialwidget.h \
    ../../Classes/CppQtLedDisplayWidget/qtleddisplaywidget.h \
    ../../Classes/CppQtLedWidget/qtledwidget.h \
    ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.h \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppWidget/widget.h \
    qtsimmysterymachineinstructionsdialog.h \
    qtsimmysterymachinemaindialog.h \
    qtsimmysterymachinemenudialog.h \
    qtsimmysterymachinerealmachinedialog.h \
    simmysterymachinemenudialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtsimmysterymachineinstructionsdialog.ui \
    qtsimmysterymachinemaindialog.ui \
    qtsimmysterymachinemenudialog.ui \
    qtsimmysterymachinerealmachinedialog.ui

RESOURCES += \
    ToolSimMysteryMachine.qrc

#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Boost
#
#
win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}
