QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES +=\
    qtmain.cpp \
    qtqmakewatchermaindialog.cpp \
    qtqmakewatchermenudialog.cpp \
    qmakewatchermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += \
    qtqmakewatchermaindialog.h \
    qtqmakewatchermenudialog.h \
    qmakewatchermenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h

FORMS    += \
    qtqmakewatchermaindialog.ui \
    qtqmakewatchermenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

OTHER_FILES += \
    Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
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

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++ -Werror

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
