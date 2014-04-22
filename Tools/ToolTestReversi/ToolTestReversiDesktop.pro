include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific for this application
#Console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppReversi/CppReversi.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)

#Desktop
include(../../Tools/ToolTestReversi/ToolTestReversiDesktop.pri)

SOURCES += qtmain.cpp
