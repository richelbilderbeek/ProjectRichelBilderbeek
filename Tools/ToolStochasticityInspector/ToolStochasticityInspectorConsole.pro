include(../../ConsoleApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Console
include(../../Classes/CppOrnsteinUhlenbeck/CppOrnsteinUhlenbeck.pri)
include(../../Classes/CppBrownianMotion/CppBrownianMotion.pri)
include(../../Classes/CppPositiveNonZeroDouble/CppPositiveNonZeroDouble.pri)

#Desktop
include(ToolStochasticityInspectorConsole.pri)

SOURCES += main.cpp
