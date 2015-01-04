#apfloat gives compile warnings with -Weffc++
include(../../DesktopApplicationNoWeffcpp.pri)

include(../../Libraries/Apfloat.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/Qwt.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

include(../../Classes/CppTempLocale/CppTempLocale.pri)

include(ToolTestFunctionParserDesktop.pri)

SOURCES += \
    qtmain.cpp
