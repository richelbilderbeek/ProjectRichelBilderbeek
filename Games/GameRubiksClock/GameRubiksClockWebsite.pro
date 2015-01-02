include(../../WebApplication.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Wt.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDial/CppDial.pri)
include(../../Classes/CppDialWidget/CppDialWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppRubiksClock/CppRubiksClock.pri)
include(../../Classes/CppRubiksClockWidget/CppRubiksClockWidget.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppToggleButton/CppToggleButton.pri)
include(../../Classes/CppToggleButtonWidget/CppToggleButtonWidget.pri)
include(../../Classes/CppTribool/CppTribool.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific, web
include(../../Classes/CppWtDialWidget/CppWtDialWidget.pri)
include(../../Classes/CppWtRubiksClockWidget/CppWtRubiksClockWidget.pri)
include(../../Classes/CppWtToggleButtonWidget/CppWtToggleButtonWidget.pri)

include(GameRubiksClockWebsite.pri)

SOURCES += wtmain.cpp
