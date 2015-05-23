include(../../DesktopApplicationNoWeffcpp.pri) #Qwt does not work with -Weffc++
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Qwt.pri)

include(../../Classes/CppPaperRockScissors/CppPaperRockScissors.pri)
include(../../Classes/CppPaperRockScissorsSimulation/CppPaperRockScissorsSimulation.pri)
include(../../Classes/CppQtPaperRockScissorsSimulation/CppQtPaperRockScissorsSimulation.pri)

include(ToolPaperRockScissorsWithTraitDesktop.pri)

SOURCES += qtmain.cpp
