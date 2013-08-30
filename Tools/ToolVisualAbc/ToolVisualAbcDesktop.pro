QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

LIBS += -lboost_system -lboost_filesystem
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppMusic \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += \
    checkprerequisites.cpp \
    chords.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    maindialog.cpp \
    menudialog.cpp \
    qtchordsdialog.cpp \
    qtmain.cpp \
    qtmaindialog.cpp \
    qtvisualabcmenudialog.cpp

HEADERS  += \
    checkprerequisites.h \
    chords.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppTrace/trace.h \
    maindialog.h \
    menudialog.h \
    qtchordsdialog.h \
    qtmaindialog.h \
    qtvisualabcmaindialog.h \
    qtvisualabcmenudialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtchordsdialog.ui \
    qtmaindialog.ui \
    qtvisualabcmenudialog.ui

RESOURCES += \
    ToolVisualAbc.qrc

OTHER_FILES += \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppTrace/Licence.txt
