QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


RESOURCES += \
    ToolTestAbout.qrc

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += main.cpp\
        qttestaboutmaindialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += qttestaboutmaindialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS    += qttestaboutmaindialog.ui \
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
    ../../Classes/CppQtHideAndShowDialog/Licence.txt
