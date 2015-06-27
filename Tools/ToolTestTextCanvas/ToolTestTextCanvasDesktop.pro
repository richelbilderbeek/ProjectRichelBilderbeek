include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific for this application
#Console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
#Desktop
include(../../Classes/CppQtDotMatrix/CppQtDotMatrix.pri)
include(../../Classes/CppQtCanvas/CppQtCanvas.pri)
include(../../Tools/ToolTestTextCanvas/ToolTestTextCanvasDesktop.pri)

SOURCES += qtmain.cpp
