include(../../ConsoleApplication.pri)

include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific, console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppXml/CppXml.pri)
include(../../Tools/ToolTestPlane/ToolTestPlaneConsole.pri)

SOURCES += main.cpp
