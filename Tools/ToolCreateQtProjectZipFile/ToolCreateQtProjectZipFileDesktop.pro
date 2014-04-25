include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Console, specific
include(../../Classes/CppQrcFile/CppQrcFile.pri)
include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)

#Desktop, specific
include(ToolCreateQtProjectZipFileDesktop.pri)

SOURCES += qtmain.cpp


