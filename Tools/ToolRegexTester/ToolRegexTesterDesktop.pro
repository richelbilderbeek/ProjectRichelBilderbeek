include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)

#Specific, desktop
include(../../Tools/ToolRegexTester/ToolRegexTesterDesktop.pri)

SOURCES += qtmain.cpp
