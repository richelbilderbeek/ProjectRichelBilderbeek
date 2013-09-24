QT += core
QT -= gui
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    toolgraycodermenudialog.cpp \
    toolgraycodermaindialog.cpp \
    main.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    toolgraycodermenudialog.h \
    toolgraycodermaindialog.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

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
