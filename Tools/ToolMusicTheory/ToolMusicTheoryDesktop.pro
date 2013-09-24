QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH +=  \
    ../../Classes/CppAbout \
    ../../Classes/CppMusic \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
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
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    musictheorymenudialog.h \
    qtchordedge.h \
    qtchordrelationswidget.h \
    qtchordvertex.h \
    qtmultiscalechordrelationswidget.h \
    qtmusictheorymenudialog.h \
    qtmusictheorymultiscaledialog.h \
    qtmusictheorysinglescaledialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtmusictheorymenudialog.ui \
    qtmusictheorymultiscaledialog.ui \
    qtmusictheorysinglescaledialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    crosscompiletowindows.sh

RESOURCES += \
    ToolMusicTheory.qrc


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
