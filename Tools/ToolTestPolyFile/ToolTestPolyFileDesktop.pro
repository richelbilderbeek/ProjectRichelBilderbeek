include(../../DesktopApplication.pri)

include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific for this application
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppPolyFile/CppPolyFile.pri)
include(../../Tools/ToolTestPolyFile/ToolTestPolyFileDesktop.pri)

SOURCES += qtmain.cpp
