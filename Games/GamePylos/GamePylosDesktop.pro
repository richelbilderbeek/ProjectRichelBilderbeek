include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppPylos/CppPylos.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)

#Specific, desktop
include(../../Classes/CppQtPylos/CppQtPylos.pri)

include(GamePylosDesktop.pri)

SOURCES += qtmain.cpp
