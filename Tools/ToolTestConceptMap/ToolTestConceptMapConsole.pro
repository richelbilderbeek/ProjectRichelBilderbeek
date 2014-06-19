include(../../ConsoleApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific
include(../../Tools/ToolTestConceptMap/ToolTestConceptMapConsole.pri)
include(../../Classes/CppConceptMap/CppConceptMap.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppXml/CppXml.pri)
SOURCES += main.cpp

# gcov
# QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
# QMAKE_LFLAGS += -lgcov -coverage
