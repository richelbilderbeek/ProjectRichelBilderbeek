include(../../ConsoleApplication.pri)

include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)

#Specific, console
include(../../Classes/CppCanvas/CppCanvas.pri)
include(../../Classes/CppConnectThree/CppConnectThree.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppConnectThreeWidget/CppConnectThreeWidget.pri)

include(GameConnectThreeConsole.pri)

SOURCES += main.cpp
