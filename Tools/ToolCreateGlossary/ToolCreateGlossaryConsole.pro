QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppHtmlPage \
  ../../Classes/CppTrace

SOURCES += main.cpp \
    ../../Classes/CppHtmlPage/htmlpage.cpp \
    createglossarymaindialog.cpp

HEADERS += \
    ../../Classes/CppHtmlPage/htmlpage.h \
    createglossarymaindialog.h \
    ../../Classes/CppTrace/trace.h

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
    ../../Classes/CppTrace/Licence.txt
