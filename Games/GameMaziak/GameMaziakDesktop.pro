QT       += core gui
TARGET = GameMaziak
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog


SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qtmain.cpp \
    qtmaziakmenudialog.cpp \
    qtmaziakmaindialog.cpp \
    qtmaziakinstructionsdialog.cpp \
    maziakmenudialog.cpp \
    qtmaziakgameoverdialog.cpp \
    qtmaziakgamewondialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qtmaziakmenudialog.h \
    qtmaziakmaindialog.h \
    qtmaziakinstructionsdialog.h \
    maziakmenudialog.h \
    qtmaziakgameoverdialog.h \
    qtmaziakgamewondialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtmaziakmenudialog.ui \
    qtmaziakmaindialog.ui \
    qtmaziakinstructionsdialog.ui \
    qtmaziakgameoverdialog.ui \
    qtmaziakgamewondialog.ui

RESOURCES += \
    gamemaziak.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt
