
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Wt.pri)
include(../../WebApplication.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Specific, console
include(../../Classes/CppCodeToHtml/CppCodeToHtml.pri)
include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppQrcFile/CppQrcFile.pri)
include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)

#Specific
include(ToolCodeToHtmlWebsite.pri)

SOURCES += wtmain.cpp
