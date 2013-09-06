QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppAsciiArter \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppAsciiArter/asciiarter.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    asciiartermaindialog.cpp \
    asciiartermenudialog.cpp \
    qtasciiartermaindialog.cpp \
    qtasciiartermenudialog.cpp \
    qtmain.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAsciiArter/asciiarter.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    asciiartermaindialog.h \
    asciiartermenudialog.h \
    qtasciiartermaindialog.h \
    qtasciiartermenudialog.h

FORMS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtasciiartermaindialog.ui \
    qtasciiartermenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppAsciiArter/Licence.txt \
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

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

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
