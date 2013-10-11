QT += core
QT -= gui
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppDotMatrix \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    tooldotmatrixmenudialog.cpp \
    main.cpp \
    ../../Classes/CppDotMatrix/dotmatrixchar.cpp \
    ../../Classes/CppDotMatrix/dotmatrixstring.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    tooldotmatrixmenudialog.h \
    ../../Classes/CppDotMatrix/dotmatrixchar.h \
    ../../Classes/CppDotMatrix/dotmatrixstring.h

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
