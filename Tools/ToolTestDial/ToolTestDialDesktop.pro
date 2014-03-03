include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)

#General, console
include(../../Libraries/GeneralConsole.pri)

#General, desktop
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppDial/CppDial.pri)
include(../../Classes/CppDialWidget/CppDialWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop
include(../../Classes/CppQtDialWidget/CppQtDialWidget.pri)
include(../../Classes/CppRainbow/CppRainbow.pri)
include(../../Tools/ToolTestDial/ToolTestDialDesktop.pri)

SOURCES += qtmain.cpp
