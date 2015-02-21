include(../../ConsoleApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)

#Specific
include(ToolWktToSvgConsole.pri)

SOURCES += main.cpp
