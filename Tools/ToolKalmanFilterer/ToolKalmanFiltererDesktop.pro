include(../../DesktopApplicationNoWeffcpp.pri) #Qwt does not go well with -Weffc++

include(../../Libraries/Boost.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Qwt.pri)

include(../../Classes/CppContainer/CppContainer.pri)
include(../../Classes/CppKalmanFilter/CppKalmanFilter.pri)
include(../../Classes/CppMatrix/CppMatrix.pri)
include(../../Classes/CppQtMatrix/CppQtMatrix.pri)
include(../../Classes/CppQtModel/CppQtModel.pri)
include(../../Classes/CppRibiRandom/CppRibiRandom.pri)
include(../../Classes/CppRibiRegex/CppRibiRegex.pri)
include(../../Classes/CppTempLocale/CppTempLocale.pri)
include(ToolKalmanFiltererDesktop.pri)

SOURCES += qtmain.cpp
