include(../../DesktopApplicationNoWeffcpp.pri)

include(../../Libraries/BoostAll.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppDnaSequence/CppDnaSequence.pri)
include(../../Classes/CppDnaR/CppDnaR.pri)
include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPedigree/CppPedigree.pri)
include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)
include(../../Classes/CppQtNewickDisplay/CppQtNewickDisplay.pri)
include(../../Classes/CppQtDnaSequencesDisplay/CppQtDnaSequencesDisplay.pri)
include(ToolFisherWrighterDesktop.pri)

SOURCES += ../../Tools/ToolFisherWrighter/qtmain.cpp
