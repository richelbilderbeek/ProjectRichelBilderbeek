include(../../DesktopApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/FParser.pri)
include(../../Libraries/Qwt.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop
include(../../Tools/ToolFunctionPlotter/ToolFunctionPlotterDesktop.pri)

SOURCES += qtmain.cpp
