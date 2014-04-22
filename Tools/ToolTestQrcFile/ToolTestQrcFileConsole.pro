include(../../ConsoleApplication.pri)

include(../../Libraries/Boost.pri)

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Specific, console
include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)
include(../../Classes/CppQrcFile/CppQrcFile.pri)

include(../../Tools/ToolTestQrcFile/ToolTestQrcFileConsole.pri)

SOURCES += main.cpp
