
include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppOpenFoam/CppOpenFoam.pri)
include(../../Classes/CppPhp/CppPhp.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppTriangleFile/CppTriangleFile.pri)
include(../../Classes/CppTriangleMesh/CppTriangleMesh.pri)
include(../../Classes/CppXml/CppXml.pri)
include(../../Tools/ToolTriangle/ToolTriangleConsole.pri)

#Desktop
include(../../Classes/CppQtNavigationableGraphicsView/CppQtNavigationableGraphicsView.pri)
include(../../Tools/ToolTriangleMeshCreator/ToolTriangleMeshCreatorDesktop.pri)

SOURCES += qtmain.cpp
