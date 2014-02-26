include(../../ConsoleApplication.pri)

include(../../Libraries/Boost.pri)

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppPylos/CppPylos.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)

include(GamePylosConsole.pri)

SOURCES += main.cpp
