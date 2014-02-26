include(../../ConsoleApplication.pri)

#Libs
include(../../Libraries/Boost.pri)
#include(../../Libraries/Fparser.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppReversi/CppReversi.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Games/GameReversi/GameReversiConsole.pri)

SOURCES += main.cpp
