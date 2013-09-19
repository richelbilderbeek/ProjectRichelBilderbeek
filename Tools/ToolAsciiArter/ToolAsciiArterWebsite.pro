QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppAsciiArter \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig

SOURCES += \
  asciiartermaindialog.cpp \
  wtmain.cpp \
  wtasciiartermaindialog.cpp \
  ../../Classes/CppAsciiArter/asciiarter.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp

HEADERS  += \
  asciiartermaindialog.h \
  wtasciiartermaindialog.h \
  ../../Classes/CppAsciiArter/asciiarter.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h

RESOURCES += \
    ToolAsciiArter.qrc

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

#
#
#
#
#

unix {
  LIBS += -lwt -lwthttp
}
