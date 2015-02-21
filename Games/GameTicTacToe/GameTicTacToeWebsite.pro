include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../WebApplication.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppTicTacToe/CppTicTacToe.pri)

#Specific, web
include(../../Classes/CppWtTicTacToeWidget/CppWtTicTacToeWidget.pri)
include(GameTicTacToeWebsite.pri)

SOURCES += wtmain.cpp
