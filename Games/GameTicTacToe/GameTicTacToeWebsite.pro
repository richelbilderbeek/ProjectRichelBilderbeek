<<<<<<< HEAD
<<<<<<< HEAD
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../WebApplication.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppTicTacToe/CppTicTacToe.pri)
include(GameTicTacToeConsole.pri)

#Specific, web
include(../../Classes/CppWtTicTacToeWidget/CppWtTicTacToeWidget.pri)
include(GameTicTacToeWebsite.pri)
=======
=======
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf
include(../../WebApplication.pri)

include(../../Libraries/Boost.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#General, web
include(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
include(../../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppTicTacToe/CppTicTacToe.pri)

#Specific, web
#include(../../Classes/CppWtTicTacToeWidget/CppWtTicTacToeWidget.pri)
<<<<<<< HEAD
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf
=======
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf

SOURCES += wtmain.cpp
