QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog

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
    qtboenkensprite.cpp \
    qtboenkenspriteball.cpp \
    qtboenkenspritemoving.cpp \
    qtboenkenspritenonmoving.cpp \
    qtboenkenspriteplayer.cpp \
    qtboenkengame.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

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
    qtboenkensprite.h \
    qtboenkenspriteball.h \
    qtboenkenspritemoving.h \
    qtboenkenspritenonmoving.h \
    qtboenkenspriteplayer.h \
    qtboenkengame.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

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
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt


#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#
win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
