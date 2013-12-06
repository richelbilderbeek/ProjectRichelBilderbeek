include(../../DesktopApplication.pri)

include(../../Libraries/Boost.pri)
include(../../Libraries/BigInteger.pri)

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#Specific
include(../../Classes/CppBinaryNewickVector/CppBinaryNewickVector.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppNewick/CppNewick.pri)
include(../../Classes/CppSortedBinaryNewickVector/CppSortedBinaryNewickVector.pri)

#Specific
include(../../Tools/ToolTestBinaryNewickVector/ToolTestBinaryNewickVectorDesktop.pri)

SOURCES += qtmain.cpp
