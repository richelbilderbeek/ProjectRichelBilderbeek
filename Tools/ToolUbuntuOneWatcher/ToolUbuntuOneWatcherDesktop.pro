QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppFileIo \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES +=\
    qtmain.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    toolubuntuonewatchermenudialog.cpp \
    qttoolubuntuonewatchermenudialog.cpp \
    qttoolubuntuonewatchermaindialog.cpp \
    ../../Classes/CppFileIo/fileio.cpp

HEADERS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    toolubuntuonewatchermenudialog.h \
    qttoolubuntuonewatchermenudialog.h \
    qttoolubuntuonewatchermaindialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppFileIo/fileio.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttoolubuntuonewatchermaindialog.ui \
    qttoolubuntuonewatchermenudialog.ui

RESOURCES += \
    ToolUbuntuOneWatcher.qrc

OTHER_FILES += \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppFileIo/Licence.txt


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
