include(../../DesktopApplication.pri)

#Libs
include(../../Libraries/Boost.pri)

#Console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#Desktop
include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#Specific for this application
include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)
include(../../Classes/CppQrcFile/CppQrcFile.pri)
include(../../Tools/ToolTestQrcFile/ToolTestQrcFileDesktop.pri)

SOURCES += qtmain.cpp
