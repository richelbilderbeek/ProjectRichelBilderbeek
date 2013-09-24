QT += core
QT -= gui

TEMPLATE = app


INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppTrace

SOURCES += main.cpp \
    regextestermaindialog.cpp \
    regextestermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    regextesterqtmaindialog.cpp \
    regextestercpp11maindialog.cpp \
    regextesterboostregexmaindialog.cpp \
    regextesterboostxpressivemaindialog.cpp \
    regextestertr1maindialog.cpp

HEADERS += \
    regextestermaindialog.h \
    regextestermenudialog.h \
    ../../Classes/CppAbout/about.h \
    regextesterqtmaindialog.h \
    regextestercpp11maindialog.h \
    regextesterboostregexmaindialog.h \
    regextesterboostxpressivemaindialog.h \
    ../../Classes/CppTrace/trace.h \
    regextestertr1maindialog.h

OTHER_FILES += \
    ../../Classes/CppTrace/Licence.txt \
    crosscompiletowindows.sh

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
  LIBS += \
    -lboost_program_options \
    -lboost_regex
}
