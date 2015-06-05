QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Qwt.pri)

#Console
include(../../Classes/CppBrownianMotion/CppBrownianMotion.pri)
include(../../Classes/CppOrnsteinUhlenbeck/CppOrnsteinUhlenbeck.pri)
include(../../Classes/CppRibiApfloat/CppRibiApfloat.pri)
include(../../Classes/CppUnits/CppUnits.pri)

#Desktop
include(../../Classes/CppQtBrownianMotion/CppQtBrownianMotion.pri)
include(../../Classes/CppQtOrnsteinUhlenbeck/CppQtOrnsteinUhlenbeck.pri)
include(ToolStochasticityInspectorDesktop.pri)

SOURCES += qtmain.cpp
