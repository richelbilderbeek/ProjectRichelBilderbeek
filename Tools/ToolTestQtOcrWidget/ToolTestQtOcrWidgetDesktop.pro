include(../../DesktopApplicationNoWeffcpp.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/Tesseract.pri) #Cannot use -Weffc++

include(../../Tools/ToolTestQtOcrWidget/ToolTestOcrWidgetDesktop.pri)

SOURCES += \
    qtmain.cpp



