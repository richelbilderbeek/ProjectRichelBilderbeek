QT       += core gui widgets

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppHtmlPage \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppHtmlPage/htmlpage.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    createglossarymaindialog.cpp \
    createglossarymenudialog.cpp \
    qtcreateglossarymaindialog.cpp \
    qtcreateglossarymenudialog.cpp \
    qtmain.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppHtmlPage/htmlpage.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
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
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolCreateGlossary.qrc

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
