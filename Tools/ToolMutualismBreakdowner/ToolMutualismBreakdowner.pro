#Qwt does not go together with Qwt
include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Qwt.pri)
include(../../Libraries/GeneralConsole.pri)

include(ToolMutualismBreakdownerDesktop.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent opengl printsupport

SOURCES += main.cpp
