include(../../DesktopApplicationNoWeffcpp.pri) #Qwt does not work with -Weffc++
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Qwt.pri)

include(../../Classes/CppPaperRockScissors/CppPaperRockScissors.pri)
include(../../Classes/CppPaperRockScissorsWithTraitSimulation/CppPaperRockScissorsWithTraitSimulation.pri)
include(../../Classes/CppQtPaperRockScissorsWithTraitSimulation/CppQtPaperRockScissorsWithTraitSimulation.pri)

include(ToolPaperRockScissorsWithTraitDesktop.pri)

SOURCES += qtmain.cpp
