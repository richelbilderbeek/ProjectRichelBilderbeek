include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/FParser.pri)

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
include(../../Tools/ToolSurfacePlotter/ToolSurfacePlotterDesktop.pri)
include(../../Classes/CppQtSurfacePlotWidget/CppQtSurfacePlotWidget.pri)

SOURCES += qtmain.cpp
