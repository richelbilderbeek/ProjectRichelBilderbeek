include(../../DesktopApplicationNoWeffcpp.pri)

include(../../Libraries/BoostAll.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPedigree/CppPedigree.pri)
include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)
include(ToolFisherWrighterDesktop.pri)

SOURCES += ../../Tools/ToolFisherWrighter/qtmain.cpp
