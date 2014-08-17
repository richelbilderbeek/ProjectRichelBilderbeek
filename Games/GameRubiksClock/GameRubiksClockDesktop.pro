include(../../DesktopApplication.pri)

include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDial/CppDial.pri)
include(../../Classes/CppDialWidget/CppDialWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppRubiksClock/CppRubiksClock.pri)
include(../../Classes/CppRubiksClockWidget/CppRubiksClockWidget.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppToggleButton/CppToggleButton.pri)
include(../../Classes/CppToggleButtonWidget/CppToggleButtonWidget.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, desktop
include(../../Classes/CppQtDialWidget/CppQtDialWidget.pri)
include(../../Classes/CppQtRubiksClockWidget/CppQtRubiksClockWidget.pri)
include(../../Classes/CppQtToggleButtonWidget/CppQtToggleButtonWidget.pri)

include(GameRubiksClockDesktop.pri)

SOURCES += qtmain.cpp
