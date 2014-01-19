include(../../ConsoleApplication.pri)
include(../../Libraries/Boost.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppLed/CppLed.pri)
include(../../Classes/CppLedWidget/CppLedWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppWidget/CppWidget.pri)

include(../../Tools/ToolTestLed/ToolTestLedConsole.pri)

SOURCES += main.cpp
