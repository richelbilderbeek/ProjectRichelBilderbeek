include(../../DesktopApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppOpenFoam/CppOpenFoam.pri)
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
include(../../Tools/ToolTriangleMeshCreator/ToolTriangleMeshCreatorDesktop.pri)

#gprof
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg


SOURCES += qtmain.cpp
