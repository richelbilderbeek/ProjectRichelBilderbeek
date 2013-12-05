include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/FParser.pri)

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#Specific, console

#Specific, desktop
include(../../Tools/ToolSurfacePlotter/ToolSurfacePlotterDesktop.pri)
include(../../Classes/CppQtSurfacePlotWidget/CppQtSurfacePlotWidget.pri)

SOURCES += qtmain.cpp
