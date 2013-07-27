QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = app

INCLUDEPATH +=  \
    ../../Classes/CppAbout \
    ../../Classes/CppMusic \
    ../../Classes/CppQtCreatorProFilebbb \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += \
     ../../Classes/CppMusic/musicnote.cpp \
     ../../Classes/CppMusic/musicchord.cpp \
     ../../Classes/CppMusic/musicscale.cpp \
    qtmain.cpp \
    qtchordrelationswidget.cpp \
    qtchordedge.cpp \
    qtmusictheorymenudialog.cpp \
    musictheorymenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qtchordvertex.cpp \
    qtmultiscalechordrelationswidget.cpp \
    qtmusictheorysinglescaledialog.cpp \
    qtmusictheorymultiscaledialog.cpp

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

