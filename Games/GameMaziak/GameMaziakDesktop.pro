include(../../DesktopApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
#include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRandom/CppRibiRandom.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppWidget/CppWidget.pri)

#Specific, desktop
#include(../../Classes/CppQtCanvas/CppQtCanvas.pri)
include(GameMaziakDesktop.pri)

SOURCES += qtmain.cpp
