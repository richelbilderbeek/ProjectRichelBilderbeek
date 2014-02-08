include(../../WebApplication.pri)

include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppAsciiArter/CppAsciiArter.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#General, web
include(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
include(../../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDial/CppDial.pri)
include(../../Classes/CppDialWidget/CppDialWidget.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppDrawCanvas/CppDrawCanvas.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
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

include(../../Games/GameRubiksClock/GameRubiksClockWebsite.pri)

SOURCES += wtmain.cpp
