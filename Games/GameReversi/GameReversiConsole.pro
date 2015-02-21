include(../../ConsoleApplication.pri)

#Libs
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
#include(../../Libraries/Fparser.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppReversi/CppReversi.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Games/GameReversi/GameReversiConsole.pri)

SOURCES += main.cpp
