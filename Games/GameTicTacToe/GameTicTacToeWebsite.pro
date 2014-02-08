include(../../WebApplication.pri)

include(../../Libraries/Boost.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppAsciiArter/CppAsciiArter.pri)
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

SOURCES += wtmain.cpp
