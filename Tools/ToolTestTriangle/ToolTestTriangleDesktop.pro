#DEFINES += TODO_ISSUE_207

include(../../DesktopApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppOpenFoam/CppOpenFoam.pri) #Really need it
include(../../Classes/CppPhp/CppPhp.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppPolyFile/CppPolyFile.pri)
include(../../Classes/CppPolyFileFromPolygons/CppPolyFileFromPolygons.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppTriangleFile/CppTriangleFile.pri)
include(../../Classes/CppTriangleMesh/CppTriangleMesh.pri)
include(../../Classes/CppXml/CppXml.pri)
#include(../../Tools/ToolTriangle/ToolTriangleConsole.pri)
#include(../../Tools/ToolTriangleCpp/ToolTriangleCppConsole.pri)

#Desktop
include(../../Classes/CppQtNavigationableGraphicsView/CppQtNavigationableGraphicsView.pri)
include(../../Tools/ToolTestTriangle/ToolTestTriangleDesktop.pri)

SOURCES += qtmain.cpp

