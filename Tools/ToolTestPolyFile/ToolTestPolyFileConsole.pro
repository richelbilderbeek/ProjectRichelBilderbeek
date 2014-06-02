include(../../ConsoleApplication.pri)

include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific, console
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppPolyFile/CppPolyFile.pri)

include(../../Tools/ToolTestPolyFile/ToolTestPolyFileConsole.pri)

SOURCES += main.cpp
