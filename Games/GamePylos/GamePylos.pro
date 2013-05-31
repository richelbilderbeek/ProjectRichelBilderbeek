#-------------------------------------------------
#
# Project created by QtCreator 2010-09-22T10:16:35
#
#-------------------------------------------------

QT       += core gui


QMAKE_CXXFLAGS += -std=c++0x
TARGET = GamePylos
TEMPLATE = app

LIBS += \
  -lboost_regex

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppPylos \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtPylos \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    qtpyloswondialog.cpp \
    qtpylosmenudialog.cpp \
    qtpylosmaindialog.cpp \
    qtpylosinstructionsdialog.cpp \
    ../../Classes/CppQtPylos/qtpyloswidget.cpp \
    ../../Classes/CppQtPylos/qtpylossprites.cpp \
    ../../Classes/CppQtPylos/qtpylosgamewidget.cpp \
    ../../Classes/CppQtPylos/qtpylosboardwidget.cpp \
    ../../Classes/CppPylos/pyloswinner.cpp \
    ../../Classes/CppPylos/pylospositionstate.cpp \
    ../../Classes/CppPylos/pylosplayer.cpp \
    ../../Classes/CppPylos/pylosmustremovestate.cpp \
    ../../Classes/CppPylos/pylosmove.cpp \
    ../../Classes/CppPylos/pylosgame.cpp \
    ../../Classes/CppPylos/pyloscurrentmovestate.cpp \
    ../../Classes/CppPylos/pyloscoordinat.cpp \
    ../../Classes/CppPylos/pylosboard.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    pylosmenudialog.cpp

HEADERS  += \
    qtpyloswondialog.h \
    qtpylosmenudialog.h \
    qtpylosmaindialog.h \
    qtpylosinstructionsdialog.h \
    ../../Classes/CppQtPylos/qtpyloswidget.h \
    ../../Classes/CppQtPylos/qtpylossprites.h \
    ../../Classes/CppQtPylos/qtpylosgamewidget.h \
    ../../Classes/CppQtPylos/qtpylosboardwidget.h \
    ../../Classes/CppPylos/pyloswinner.h \
    ../../Classes/CppPylos/pylospositionstate.h \
    ../../Classes/CppPylos/pylosplayer.h \
    ../../Classes/CppPylos/pylosmustremovestate.h \
    ../../Classes/CppPylos/pylosmove.h \
    ../../Classes/CppPylos/pylosgame.h \
    ../../Classes/CppPylos/pylosfwd.h \
    ../../Classes/CppPylos/pyloscurrentmovestate.h \
    ../../Classes/CppPylos/pyloscoordinat.h \
    ../../Classes/CppPylos/pylosboard.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppAbout/about.h \
    pylosmenudialog.h \
    ../../Classes/CppTrace/trace.h

FORMS    += \
    qtpyloswondialog.ui \
    qtpylosmenudialog.ui \
    qtpylosmaindialog.ui \
    qtpylosinstructionsdialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    GamePylos.qrc

OTHER_FILES += \
    ../../Classes/CppQtPylos/Licence.txt \
    ../../Classes/CppPylos/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppTrace/Licence.txt
