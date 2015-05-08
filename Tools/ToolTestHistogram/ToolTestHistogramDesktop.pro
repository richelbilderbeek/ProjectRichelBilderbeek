include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Qwt.pri)

#Specific, console
include(../../Classes/CppHistogram/CppHistogram.pri)
include(ToolTestHistogramDesktop.pri)

SOURCES += qtmain.cpp
