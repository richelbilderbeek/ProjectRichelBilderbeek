#apfloat gives compile warnings with -Weffc++
include(../../ConsoleApplicationNoWeffcpp.pri)

#include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/FParser.pri)

include(../../Libraries/GeneralConsole.pri)

include(ToolTestFunctionParserConsole.pri)

SOURCES += main.cpp
