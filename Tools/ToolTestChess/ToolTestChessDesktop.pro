include(../../DesktopApplication.pri)

include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific
include(../../Classes/CppChess/CppChess.pri)
include(../../Classes/CppChessResources/CppChessResources.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppWidget/CppWidget.pri)

#Specific, desktop
include(../../Classes/CppQtChess/CppQtChess.pri)
include(ToolTestChessDesktop.pri)

SOURCES += qtmain.cpp
