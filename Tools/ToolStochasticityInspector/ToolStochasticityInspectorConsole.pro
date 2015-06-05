include(../../ConsoleApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Console
include(../../Classes/CppBrownianMotion/CppBrownianMotion.pri)
include(../../Classes/CppOrnsteinUhlenbeck/CppOrnsteinUhlenbeck.pri)
include(../../Classes/CppUnits/CppUnits.pri)

#Desktop
include(ToolStochasticityInspectorConsole.pri)

SOURCES += main.cpp
