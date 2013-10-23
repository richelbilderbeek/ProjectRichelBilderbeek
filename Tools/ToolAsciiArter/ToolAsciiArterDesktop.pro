QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include( ToolAsciiArter.pri )

INCLUDEPATH += \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog

SOURCES += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtasciiartermaindialog.cpp \
    qtasciiartermenudialog.cpp \
    qtmain.cpp

HEADERS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    qtasciiartermaindialog.h \
    qtasciiartermenudialog.h

FORMS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtasciiartermaindialog.ui \
    qtasciiartermenudialog.ui

OTHER_FILES += \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolAsciiArter.qrc

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
