include(../../DesktopApplication.pri)

include(../../Libraries/Boost.pri)

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#Specific
include(../../Classes/CppChess/CppChess.pri)
include(../../Classes/CppChessResources/CppChessResources.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppWidget/CppWidget.pri)

#Specific, desktop
include(../../Classes/CppQtChess/CppQtChess.pri)
include(../../Tools/ToolTestChess/ToolTestChessDesktop.pri)

SOURCES += qtmain.cpp
