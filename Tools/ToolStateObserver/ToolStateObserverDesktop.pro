QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/FParser.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Qwt.pri)

#Console
include(../../Classes/CppStateObserver/CppStateObserver.pri)

#Desktop
include(ToolStateObserverDesktop.pri)

SOURCES += qtmain.cpp

