QT       += core gui
TARGET = BoenkenDesktop
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qtboenkenmenudialog.cpp \
    boenkenmenudialog.cpp \
    qtmain.cpp \
    qtboenkenmaindialog.cpp \
    qtboenkenpresskeydialog.cpp \
    qtboenkenarenadialog.cpp \
    qtboenkencontrolsdialog.cpp \
    qtboenkenplayersdialog.cpp \
    qtboenkentraindialog.cpp \
    boenkensprite.cpp \
    boenkenspriteball.cpp \
    boenkenspritemoving.cpp \
    boenkenspritenonmoving.cpp \
    boenkenspriteplayer.cpp \
    boenkengame.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qtboenkenmenudialog.h \
    boenkenmenudialog.h \
    qtboenkenmaindialog.h \
    qtboenkenpresskeydialog.h \
    qtboenkenarenadialog.h \
    qtboenkencontrolsdialog.h \
    qtboenkenplayersdialog.h \
    qtboenkentraindialog.h \
    boenkenarenasettings.h \
    boenkencontrols.h \
    boenkensprite.h \
    boenkenspriteball.h \
    boenkenspritemoving.h \
    boenkenspritenonmoving.h \
    boenkenspriteplayer.h \
    boenkengame.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtboenkenmenudialog.ui \
    qtboenkenmaindialog.ui \
    qtboenkenpresskeydialog.ui \
    qtboenkenarenadialog.ui \
    qtboenkencontrolsdialog.ui \
    qtboenkenplayersdialog.ui \
    qtboenkentraindialog.ui

RESOURCES += \
    GameBoenken.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt
