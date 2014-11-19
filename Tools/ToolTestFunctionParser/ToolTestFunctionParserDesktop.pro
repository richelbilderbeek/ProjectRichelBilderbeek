#apfloat gives compile warnings with -Weffc++
include(../../DesktopApplicationNoWeffcpp.pri)

include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/Qwt.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

include(ToolTestFunctionParserDesktop.pri)

SOURCES += \
    qtmain.cpp
