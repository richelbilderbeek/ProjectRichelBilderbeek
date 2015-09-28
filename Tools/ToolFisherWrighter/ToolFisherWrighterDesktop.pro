include(../../DesktopApplicationSloppy.pri) # RInside goes bad with -Wextra
include(../../Libraries/BoostAll.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Rinside.pri)

#Specific
include(../../Classes/CppBeast/CppBeast.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppDnaSequence/CppDnaSequence.pri)
include(../../Classes/CppDnaR/CppDnaR.pri)
include(../../Classes/CppFastaFile/CppFastaFile.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPedigree/CppPedigree.pri)
include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)
include(../../Classes/CppRibiRinside/CppRibiRinside.pri)
include(../../Classes/CppQtBeastDisplay/CppQtBeastDisplay.pri)
include(../../Classes/CppQtNewickDisplay/CppQtNewickDisplay.pri)
include(../../Classes/CppQtDnaSequencesDisplay/CppQtDnaSequencesDisplay.pri)
include(ToolFisherWrighterDesktop.pri)

SOURCES += ../../Tools/ToolFisherWrighter/qtmain.cpp
