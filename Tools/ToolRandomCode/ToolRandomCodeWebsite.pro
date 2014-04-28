include(../../WebApplication.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppRandomCode/CppRandomCode.pri)

#Specific, website
include(ToolRandomCodeWebsite.pri)

SOURCES += wtmain.cpp
