include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/BigInteger.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific
include(../../Classes/CppBinaryNewickVector/CppBinaryNewickVector.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppNewick/CppNewick.pri)
include(../../Classes/CppTwoDigitNewick/CppTwoDigitNewick.pri)
include(ToolTestTwoDigitNewickDesktop.pri)

SOURCES += qtmain.cpp
