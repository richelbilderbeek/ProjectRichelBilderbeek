include(../../DesktopApplication.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppConnectThree/CppConnectThree.pri)
include(../../Classes/CppConnectThreeWidget/CppConnectThreeWidget.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppTribool/CppTribool.pri)

#Specific, desktop
include(../../Classes/CppQtCanvas/CppQtCanvas.pri)
include(../../Classes/CppQtConnectThreeWidget/CppQtConnectThreeWidget.pri)
include(../../Games/GameConnectThree/GameConnectThreeDesktop.pri)

include(GameK3OpEenRijDesktop.pri)

SOURCES += qtmain.cpp
