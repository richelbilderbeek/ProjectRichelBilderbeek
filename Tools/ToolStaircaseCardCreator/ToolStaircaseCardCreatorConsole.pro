include(../../ConsoleApplication.pri)
include(../../Libraries/Boost.pri)

#General, console
include(../../Libraries/GeneralConsole.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Tools/ToolStaircaseCardCreator/ToolStaircaseCardCreatorConsole.pri)

SOURCES += main.cpp
