include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop
include(../../Classes/CppQtCanvas/CppQtCanvas.pri)
include(../../Tools/ToolTestDrawCanvas/ToolTestDrawCanvasDesktop.pri)

SOURCES += qtmain.cpp

