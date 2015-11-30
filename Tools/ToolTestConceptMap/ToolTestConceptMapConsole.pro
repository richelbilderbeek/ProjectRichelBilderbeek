include(../../ConsoleApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific, console
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppCoordinat/CppCoordinat.pri)
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppConceptMap/CppConceptMap.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppXml/CppXml.pri)

#Specific
include(../../Tools/ToolTestConceptMap/ToolTestConceptMapConsole.pri)
SOURCES += main.cpp

# gcov
# QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
# QMAKE_LFLAGS += -lgcov -coverage
