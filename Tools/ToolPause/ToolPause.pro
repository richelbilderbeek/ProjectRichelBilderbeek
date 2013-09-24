QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout

SOURCES += main.cpp \
    pausemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp

HEADERS += \
    pausemenudialog.h \
    ../../Classes/CppAbout/about.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt

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
