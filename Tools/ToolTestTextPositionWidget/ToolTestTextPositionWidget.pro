QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    qttextpositionwidget.cpp \
    qttextpositionitem.cpp \
    qttooltesttextpositionwidgetmaindialog.cpp \
    tooltesttextpositionwidgetmenudialog.cpp \
    qttooltesttextpositionwidgetmenudialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp

HEADERS += \
    qttextpositionwidget.h \
    qttextpositionitem.h \
    qttooltesttextpositionwidgetmaindialog.h \
    tooltesttextpositionwidgetmenudialog.h \
    qttooltesttextpositionwidgetmenudialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppTrace/trace.h

FORMS += \
    qttooltesttextpositionwidgetmaindialog.ui \
    qttooltesttextpositionwidgetmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

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

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt
