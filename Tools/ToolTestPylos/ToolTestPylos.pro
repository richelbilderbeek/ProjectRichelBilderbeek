
QT       += core gui
TARGET = TestPylosDesktop
LIBS += \
    -lboost_filesystem \
    -lboost_regex \
    -lboost_system

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppPylos \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtPylos \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppPylos/pylosboard.cpp \
    ../../Classes/CppPylos/pyloscoordinat.cpp \
    ../../Classes/CppPylos/pyloscurrentmovestate.cpp \
    ../../Classes/CppPylos/pylosgame.cpp \
    ../../Classes/CppPylos/pylosmove.cpp \
    ../../Classes/CppPylos/pylospositionstate.cpp \
    ../../Classes/CppPylos/pylosplayer.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtPylos/qtpylosboardwidget.cpp \
    ../../Classes/CppQtPylos/qtpylosgamewidget.cpp \
    ../../Classes/CppQtPylos/qtpylossprites.cpp \
    qttestpylosgametestsdialog.cpp \
    qttestpylosmenudialog.cpp \
    qttestpylostestboarddialog.cpp \
    qttestpylostestgamedialog.cpp \
    testpylosmenudialog.cpp \
    ../../Classes/CppPylos/pylosmustremovestate.cpp \
    ../../Classes/CppPylos/pyloswinner.cpp \
    ../../Classes/CppQtPylos/qtpyloswidget.cpp \
    qttestpylosrandomplaydialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppPylos/pylosboard.h \
    ../../Classes/CppPylos/pyloscoordinat.h \
    ../../Classes/CppPylos/pyloscurrentmovestate.h \
    ../../Classes/CppPylos/pylosfwd.h \
    ../../Classes/CppPylos/pylosgame.h \
    ../../Classes/CppPylos/pylosmove.h \
    ../../Classes/CppPylos/pylosplayer.h \
    ../../Classes/CppPylos/pylospositionstate.h \
    ../../Classes/CppPylos/pyloswinner.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtPylos/qtpylosboardwidget.h \
    ../../Classes/CppQtPylos/qtpylosgamewidget.h \
    ../../Classes/CppQtPylos/qtpylossprites.h \
    ../../Classes/CppTrace/trace.h \
    qttestpylosgametestsdialog.h \
    qttestpylosmenudialog.h \
    qttestpylostestboarddialog.h \
    qttestpylostestgamedialog.h \
    testpylosmenudialog.h \
    ../../Classes/CppPylos/pylosmustremovestate.h \
    ../../Classes/CppQtPylos/qtpyloswidget.h \
    qttestpylosrandomplaydialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestpylosgametestsdialog.ui \
    qttestpylosmenudialog.ui \
    qttestpylostestboarddialog.ui \
    qttestpylostestgamedialog.ui \
    qttestpylosrandomplaydialog.ui

RESOURCES += \
    ToolTestPylos.qrc

OTHER_FILES += \
    ../../Classes/CppPylos/Licence.txt \
    ../../Classes/CppQtPylos/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt
