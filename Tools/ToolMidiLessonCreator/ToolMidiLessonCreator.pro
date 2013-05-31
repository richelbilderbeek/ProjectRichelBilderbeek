QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

INCLUDEPATH += \
    ../../Classes/CppAbcFile \
    ../../Classes/CppAbout \
    ../../Classes/CppMusic \
    ../../Classes/CppTrace

SOURCES += main.cpp\
    qtmidilessoncreatormaindialog.cpp \
    midilessoncreatormaindialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppAbcFile/abcfile.cpp \
    ../../Classes/CppMusic/musicbar.cpp

HEADERS  += qtmidilessoncreatormaindialog.h \
    midilessoncreatormaindialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppAbcFile/abcfile.h \
    ../../Classes/CppMusic/musicfwd.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppMusic/musicbar.h

FORMS    += qtmidilessoncreatormaindialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppTrace/Licence.txt
