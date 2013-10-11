QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    primeexpert.cpp \
    qtmain.cpp \
    qttoolprimeexpertmaindialog.cpp \
    qttoolprimeexpertmenudialog.cpp \
    toolprimeexpertmenudialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    primeexpert.h \
    qttoolprimeexpertmaindialog.h \
    qttoolprimeexpertmenudialog.h \
    toolprimeexpertmenudialog.h \
    ../../Classes/CppTrace/trace.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttoolprimeexpertmaindialog.ui \
    qttoolprimeexpertmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt

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
