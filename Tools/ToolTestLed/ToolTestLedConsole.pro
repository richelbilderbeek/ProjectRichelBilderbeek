include(../../ConsoleApplication.pri)
include(../../Libraries/Boost.pri)

#General, console
include(../../Libraries/GeneralConsole.pri)

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
