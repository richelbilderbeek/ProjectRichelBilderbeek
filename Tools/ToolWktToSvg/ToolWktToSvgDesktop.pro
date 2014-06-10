include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Console
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)

#Desktop
include(../../Classes/CppQtNavigationableGraphicsView/CppQtNavigationableGraphicsView.pri)
include(../../Tools/ToolWktToSvg/ToolWktToSvgDesktop.pri)

SOURCES += qtmain.cpp

