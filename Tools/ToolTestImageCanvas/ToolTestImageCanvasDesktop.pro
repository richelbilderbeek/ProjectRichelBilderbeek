include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific for this application
#Console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
#Desktop
include(../../Classes/CppQtCanvas/CppQtCanvas.pri)

include(ToolTestImageCanvasDesktop.pri)

SOURCES += qtmain.cpp

