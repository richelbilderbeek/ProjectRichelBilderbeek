#gprof
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

include(../../ConsoleApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

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
include(../../Tools/ToolTriangle/ToolTriangleConsole.pri)

include(../../Tools/ToolTriangleMeshCreator/ToolTriangleMeshCreatorConsole.pri)

SOURCES += main.cpp
