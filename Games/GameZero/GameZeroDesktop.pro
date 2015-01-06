include(../../DesktopApplication.pri)
include(../../Libraries/Apfloat.pri)
include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

SOURCES += \
    qtmain.cpp \
    qtzeromaindialog.cpp

RESOURCES += GameZero.qrc

FORMS += qtzeromaindialog.ui

HEADERS += qtzeromaindialog.h
