include(../../ConsoleApplicationSloppy.pri) # RInside goes bad with -Werror
include(../../Libraries/BoostAll.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Rinside.pri)

#Specific
include(../../Classes/CppBeast/CppBeast.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppDnaSequence/CppDnaSequence.pri)
include(../../Classes/CppFastaFile/CppFastaFile.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppRibiRinside/CppRibiRinside.pri)
include(ToolBeastScripterConsole.pri)

SOURCES += main.cpp
