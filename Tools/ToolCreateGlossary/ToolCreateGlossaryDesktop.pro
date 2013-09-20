QT       += core gui widgets

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppHtmlPage \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppHtmlPage/htmlpage.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    createglossarymaindialog.cpp \
    createglossarymenudialog.cpp \
    qtcreateglossarymaindialog.cpp \
    qtcreateglossarymenudialog.cpp \
    qtmain.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppHtmlPage/htmlpage.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    createglossarymaindialog.h \
    createglossarymenudialog.h \
    qtcreateglossarymaindialog.h \
    qtcreateglossarymenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtcreateglossarymaindialog.ui \
    qtcreateglossarymenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolCreateGlossary.qrc

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
