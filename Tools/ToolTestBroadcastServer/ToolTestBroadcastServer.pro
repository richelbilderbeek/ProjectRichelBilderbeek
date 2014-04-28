include(../../WebApplication.pri)
include(../../Libraries/BigInteger.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

include(../../Classes/CppWtBroadcastServer/CppWtBroadcastServer.pri)

#include(ToolTestBroadcastServer.pri)

SOURCES += wtmain.cpp \
    testbroadcastservermenudialog.cpp \
    testbroadcastserverwtmenudialog.cpp \
    testbroadcastserverwtmaindialog.cpp

HEADERS += \
    testbroadcastservermenudialog.h \
    testbroadcastserverwtmaindialog.h \
    testbroadcastserverwtmenudialog.h
