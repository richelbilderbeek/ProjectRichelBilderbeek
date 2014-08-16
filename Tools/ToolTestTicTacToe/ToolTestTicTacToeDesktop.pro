include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppTicTacToe/CppTicTacToe.pri)
include(../../Classes/CppWidget/CppWidget.pri)

#Specific, desktop
include(../../Classes/CppQtCanvas/CppQtCanvas.pri)
include(../../Classes/CppQtTicTacToeWidget/CppQtTicTacToeWidget.pri)
include(../../Tools/ToolTestTicTacToe/ToolTestTicTacToeDesktop.pri)

SOURCES += qtmain.cpp
