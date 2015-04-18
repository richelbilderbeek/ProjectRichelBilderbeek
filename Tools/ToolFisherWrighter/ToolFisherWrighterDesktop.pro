include(../../DesktopApplicationNoWeffcpp.pri)

include(../../Libraries/BoostAll.pri)
#include(../../Libraries/Qwt.pri)

#Specific
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPedigree/CppPedigree.pri)
include(../../Classes/CppPhylogenyR/CppPhylogenyR.pri)
include(../../Classes/CppTestTimer/CppTestTimer.pri)
include(../../Classes/CppTrace/CppTrace.pri)
include(ToolFisherWrighterDesktop.pri)

SOURCES += ../../Tools/ToolFisherWrighter/qtmain.cpp
