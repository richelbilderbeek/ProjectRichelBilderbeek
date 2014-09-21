QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppRandomCode

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppRandomCode/randomcode.cpp \
    qtmain.cpp \
    qtrandomcodemaindialog.cpp \
    qtrandomcodemenudialog.cpp \
    randomcodemenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppRandomCode/randomcode.h \
    qtrandomcodemaindialog.h \
    qtrandomcodemenudialog.h \
    randomcodemenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtrandomcodemaindialog.ui \
    qtrandomcodemenudialog.ui

RESOURCES += \
    ToolRandomCode.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

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
