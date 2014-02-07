include(../../DesktopApplication.pri)

include(../../Libraries/Boost.pri)

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppAsciiArter/CppAsciiArter.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppConnectThree/CppConnectThree.pri)
include(../../Classes/CppConnectThreeWidget/CppConnectThreeWidget.pri)
include(../../Classes/CppTribool/CppTribool.pri)

#Specific, desktop
include(../../Classes/CppQtConnectThreeWidget/CppQtConnectThreeWidget.pri)
include(../../Games/GameConnectThree/GameConnectThreeDesktop.pri)

include(GameK3OpEenRijDesktop.pri)

SOURCES += qtmain.cpp
