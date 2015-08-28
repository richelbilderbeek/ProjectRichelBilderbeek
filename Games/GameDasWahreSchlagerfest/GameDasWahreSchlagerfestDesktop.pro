include(../../DesktopApplication.pri)

include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppQtGraphics/CppQtGraphics.pri)
#include(../../Classes/CppQtCanvas/CppQtCanvas.pri)

include(GameDasWahreSchlagerfestDesktop.pri)

SOURCES += qtmain.cpp
