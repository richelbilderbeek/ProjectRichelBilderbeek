include(../../DesktopApplicationNoWeffcpp.pri)

include(../../Libraries/BoostAll.pri)
include(../../Libraries/Qwt.pri)

#Specific
include(../../Classes/CppPedigree/CppPedigree.pri)
include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)
include(ToolFisherWrighterDesktop.pri)

SOURCES += ../../Tools/ToolFisherWrighter/qtmain.cpp
