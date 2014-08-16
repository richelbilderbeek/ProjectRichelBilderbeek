include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../WebApplication.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppDial/CppDial.pri)
include(../../Classes/CppDialWidget/CppDialWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppLed/CppLed.pri)
include(../../Classes/CppLedWidget/CppLedWidget.pri)
include(../../Classes/CppMysteryMachine/CppMysteryMachine.pri)
include(../../Classes/CppMysteryMachineWidget/CppMysteryMachineWidget.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppToggleButton/CppToggleButton.pri)
include(../../Classes/CppToggleButtonWidget/CppToggleButtonWidget.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, web
include(../../Classes/CppWtDialWidget/CppWtDialWidget.pri)
include(../../Classes/CppWtLedWidget/CppWtLedWidget.pri)
include(../../Classes/CppWtToggleButtonWidget/CppWtToggleButtonWidget.pri)
include(../../Classes/CppWtMysteryMachineWidget/CppWtMysteryMachineWidget.pri)

include(../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineWebsite.pri)

SOURCES += wtmain.cpp
