include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppPolyFile/CppPolyFile.pri)
include(../../Classes/CppPolyFileFromPolygons/CppPolyFileFromPolygons.pri)

#Desktop
include(../../Classes/CppQtNavigationableGraphicsView/CppQtNavigationableGraphicsView.pri)
include(../../Tools/ToolTestPolyFileFromPolygons/ToolTestPolyFileFromPolygonsDesktop.pri)
include(../../Tools/ToolWktToSvg/ToolWktToSvgConsole.pri)

SOURCES += qtmain.cpp

