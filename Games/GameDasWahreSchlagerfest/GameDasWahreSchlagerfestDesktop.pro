QT       += core gui
TARGET = GameDasWahreSchlagerfest
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog


SOURCES += qtmain.cpp \
    daswahreschlagerfestmenudialog.cpp \
    qtdaswahreschlagerfestmaindialog.cpp \
    daswahreschlagerfestwidget.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qtdaswahreschlagerfestwidget.cpp \
    qtdaswahreschlagerfestmenudialog.cpp

HEADERS  += \
    qtdaswahreschlagerfestmaindialog.h \
    daswahreschlagerfestwidget.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qtdaswahreschlagerfestwidget.h \
    qtdaswahreschlagerfestmenudialog.h

FORMS    += \
    qtdaswahreschlagerfestmaindialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtdaswahreschlagerfestmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt

RESOURCES += \
    GameDasWahreSchlagerfest.qrc \
    GameDasWahreSchlagerfest.qrc
