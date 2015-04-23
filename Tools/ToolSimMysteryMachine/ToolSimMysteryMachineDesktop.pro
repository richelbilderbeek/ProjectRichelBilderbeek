include(../../DesktopApplicationNoWeffcpp.pri)

#Libs
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)

#General, console
include(../../Libraries/GeneralConsole.pri)

#General, desktop
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDial/CppDial.pri)
include(../../Classes/CppDialWidget/CppDialWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppLed/CppLed.pri)
include(../../Classes/CppLedWidget/CppLedWidget.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppMysteryMachine/CppMysteryMachine.pri)
include(../../Classes/CppMysteryMachineWidget/CppMysteryMachineWidget.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppToggleButton/CppToggleButton.pri)
include(../../Classes/CppToggleButtonWidget/CppToggleButtonWidget.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop
include(../../Classes/CppQtCanvas/CppQtCanvas.pri)
include(../../Classes/CppQtDialWidget/CppQtDialWidget.pri)
include(../../Classes/CppQtLedWidget/CppQtLedWidget.pri)
include(../../Classes/CppQtMysteryMachineWidget/CppQtMysteryMachineWidget.pri)
include(../../Classes/CppQtToggleButtonWidget/CppQtToggleButtonWidget.pri)
include(../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineDesktop.pri )

SOURCES += qtmain.cpp
