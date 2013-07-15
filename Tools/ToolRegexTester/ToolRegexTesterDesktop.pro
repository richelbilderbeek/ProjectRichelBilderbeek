QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

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
    regextesterboostmaindialog.cpp \
    regextestercpp11maindialog.cpp \
    regextestermaindialog.cpp \
    regextestermenudialog.cpp \
    regextesterqtmaindialog.cpp \
    regextestertr1maindialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qtregextestermaindialog.h \
    qtregextestermenudialog.h \
    regextesterboostmaindialog.h \
    regextestercpp11maindialog.h \
    regextestermaindialog.h \
    regextestermenudialog.h \
    regextesterqtmaindialog.h \
    regextestertr1maindialog.h

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
  message(Unix)
  QMAKE_CXXFLAGS += -Werror
}

win32 {
  !static {
    message(Native Windows)
    QMAKE_CXXFLAGS += -Werror

  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
    #Allow the crosscompiler to emit warnings without terminating
    QMAKE_CXXFLAGS += #-Werror
  }
}

#
#
# Boost
#
#

unix {
  message(Unix dynamic link to Boost)

  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {

  message(Windows dynamic link to Boost)

  INCLUDEPATH += \
    e:/Projects/Libraries/boost_1_54_0

  debug {
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-d-1_54.a
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-d-1_54.a
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-d-1_54.a
  }
  release {
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-1_54.a
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-1_54.a
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-1_54.a
  }
}
