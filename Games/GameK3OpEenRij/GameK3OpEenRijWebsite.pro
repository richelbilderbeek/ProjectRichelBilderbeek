include(../../WebApplication.pri)

include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppConnectThree/CppConnectThree.pri)
include(../../Classes/CppConnectThreeWidget/CppConnectThreeWidget.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppTribool/CppTribool.pri)

#Specific, web
include(GameK3OpEenRijWebsite.pri)
include(../../Classes/CppWtConnectThreeWidget/CppWtConnectThreeWidget.pri)
include(../../Games/GameConnectThree/GameConnectThreeWebsite.pri)

SOURCES += wtmain.cpp

#/home/richel/ProjectRichelBilderbeek/Games/GameConnectThree/qtconnectthreeresources.
