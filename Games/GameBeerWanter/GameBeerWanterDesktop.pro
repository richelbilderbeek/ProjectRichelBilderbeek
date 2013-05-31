QT += core gui
TARGET = BeerWanterDesktop
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog

SOURCES +=  \
    qtmain.cpp \
    beerwantermaindialog.cpp \
    beerwantermenudialog.cpp \
    qtbeerwanterwidget.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qtbeerwantermaindialog.cpp \
    qtbeerwantermenudialog.cpp

HEADERS += \
    beerwantermaindialog.h \
    beerwantermenudialog.h \
    qtbeerwanterwidget.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qtbeerwantermaindialog.h \
    qtbeerwantermenudialog.h


RESOURCES += \
    beerwanter.qrc

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtbeerwantermaindialog.ui \
    qtbeerwantermenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt
