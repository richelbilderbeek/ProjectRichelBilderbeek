include(../../WebApplication.pri)

include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppAsciiArter/CppAsciiArter.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#General, web
include(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
include(../../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppConnectThree/CppConnectThree.pri)
include(../../Classes/CppConnectThreeWidget/CppConnectThreeWidget.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppTribool/CppTribool.pri)
#include(../../Games/GameConnectThree/GameConnectThreeConsole.pri)

#Specific, web
include(../../Games/GameK3OpEenRij/GameK3OpEenRijWebsite.pri)
include(../../Classes/CppWtConnectThreeWidget/CppWtConnectThreeWidget.pri)
include(../../Games/GameConnectThree/GameConnectThreeWebsite.pri)

SOURCES += wtmain.cpp

#/home/richel/ProjectRichelBilderbeek/Games/GameConnectThree/qtconnectthreeresources.
