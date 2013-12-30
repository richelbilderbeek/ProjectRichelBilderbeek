include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../WebApplication.pri)

#General
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Website general
include(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
include(../../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)

#Specific
include(../../Games/GameBeerWanter/GameBeerWanterWebsite.pri)

SOURCES += wtmain.cpp
