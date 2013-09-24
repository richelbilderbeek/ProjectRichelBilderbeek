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
    qtmain.cpp \
    qtregextestermaindialog.cpp \
    qtregextestermenudialog.cpp \
    regextestercpp11maindialog.cpp \
    regextestermaindialog.cpp \
    regextestermenudialog.cpp \
    regextesterqtmaindialog.cpp \
    regextestertr1maindialog.cpp \
    regextesterboostregexmaindialog.cpp \
    regextesterboostxpressivemaindialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qtregextestermaindialog.h \
    qtregextestermenudialog.h \
    regextestercpp11maindialog.h \
    regextestermaindialog.h \
    regextestermenudialog.h \
    regextesterqtmaindialog.h \
    regextestertr1maindialog.h \
    regextesterboostregexmaindialog.h \
    regextesterboostxpressivemaindialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtregextestermaindialog.ui \
    qtregextestermenudialog.ui

RESOURCES += \
    ToolRegexTester.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    crosscompiletowindows.sh \
    Licence.txt \
    zip.sh

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

unix {
  LIBS += -lboost_regex
}
