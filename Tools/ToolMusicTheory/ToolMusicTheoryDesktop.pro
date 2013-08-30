QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
TEMPLATE = app

INCLUDEPATH +=  \
    ../../Classes/CppAbout \
    ../../Classes/CppMusic \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    musictheorymenudialog.cpp \
    qtchordedge.cpp \
    qtchordrelationswidget.cpp \
    qtchordvertex.cpp \
    qtmain.cpp \
    qtmultiscalechordrelationswidget.cpp \
    qtmusictheorymenudialog.cpp \
    qtmusictheorymultiscaledialog.cpp \
    qtmusictheorysinglescaledialog.cpp

HEADERS  += \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppTrace/trace.h \
    qtchordrelationswidget.h \
    qtchordedge.h \
    qtmusictheorymenudialog.h \
    musictheorymenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qtchordvertex.h \
    qtmultiscalechordrelationswidget.h \
    qtmusictheorysinglescaledialog.h \
    qtmusictheorymultiscaledialog.h

FORMS    += \
    qtmusictheorymenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtmusictheorysinglescaledialog.ui \
    qtmusictheorymultiscaledialog.ui

OTHER_FILES += \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    crosscompiletowindows.sh

RESOURCES += \
    ToolMusicTheory.qrc

