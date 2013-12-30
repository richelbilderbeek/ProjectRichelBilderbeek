include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../WebApplication.pri)

#General, console
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

#General, website
include(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
include(../../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)

#Specific
include(../../Classes/CppConnectThree/CppConnectThree.pri)
include(../../Classes/CppConnectThreeWidget/CppConnectThreeWidget.pri)
include(../../Classes/CppWtConnectThreeWidget/CppWtConnectThreeWidget.pri)
include(../../Games/GameConnectThree/GameConnectThreeWebsite.pri)

SOURCES += wtmain.cpp

SOURCES += \
    qtconnectthreeresources.cpp

HEADERS += \
    qtconnectthreeresources.h
