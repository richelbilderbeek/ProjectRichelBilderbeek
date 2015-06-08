#Don't enable Effective C++ warnings when using Qwt
include(../../WebApplication.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)
include(../../Libraries/Wt.pri)

include(../../Classes/CppWtSelectFileDialog/CppWtSelectFileDialog.pri)


SOURCES += \
    wtmain.cpp \
    wttestselectfiledialogmenudialog.cpp \
    wttestselectfiledialogmaindialog.cpp

HEADERS += \
    wttestselectfiledialogmenudialog.h \
    wttestselectfiledialogmaindialog.h

RESOURCES += \
    ToolTestSelectFileDialog.qrc
