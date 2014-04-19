include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/FParser.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop
include(../../Tools/ToolTestPlane/ToolTestPlaneDesktop.pri)
include(../../Classes/CppQtSurfacePlotWidget/CppQtSurfacePlotWidget.pri)

SOURCES += qtmain.cpp
