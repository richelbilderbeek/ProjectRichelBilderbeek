include(../../DesktopApplication.pri)

#Libs
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppDial/CppDial.pri)
include(../../Classes/CppDialWidget/CppDialWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppLed/CppLed.pri)
include(../../Classes/CppLedWidget/CppLedWidget.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppMysteryMachine/CppMysteryMachine.pri)
include(../../Classes/CppMysteryMachineWidget/CppMysteryMachineWidget.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppToggleButton/CppToggleButton.pri)
include(../../Classes/CppToggleButtonWidget/CppToggleButtonWidget.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Classes/CppXml/CppXml.pri)

include(../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineConsole.pri )

SOURCES += main.cpp
