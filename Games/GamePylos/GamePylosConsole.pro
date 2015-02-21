include(../../ConsoleApplication.pri)

include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppPylos/CppPylos.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)

include(GamePylosConsole.pri)

SOURCES += main.cpp
