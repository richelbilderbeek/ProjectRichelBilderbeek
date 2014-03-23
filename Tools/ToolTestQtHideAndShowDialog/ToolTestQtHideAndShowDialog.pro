include(../../DesktopApplication.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralDesktop.pri)

INCLUDEPATH += \
    ../../Classes/CppQtHideAndShowDialog

SOURCES += \
    qtmain.cpp \
    qttesthideandshowmaindialog.cpp

HEADERS += \
    qttesthideandshowmaindialog.h

FORMS += \
    qttesthideandshowmaindialog.ui
