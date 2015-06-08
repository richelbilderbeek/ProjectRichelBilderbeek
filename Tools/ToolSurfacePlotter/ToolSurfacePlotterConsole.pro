# Fparser does not work with -Weffc++
include(../../ConsoleApplicationNoWeffcpp.pri)4
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppXml/CppXml.pri)
include(../../Tools/ToolSurfacePlotter/ToolSurfacePlotterConsole.pri)

SOURCES += main.cpp
