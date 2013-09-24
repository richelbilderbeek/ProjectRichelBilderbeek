QT += core
QT -= gui qt
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtCreatorProFile

SOURCES += \
    main.cpp \
    ndsmake.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppAbout/about.cpp

QMAKE_CXX_FLAGS_WARN_ON += -Wextra

HEADERS += \
    createholymakefile.h \
    createmakefile.h \
    ndsmake.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppAbout/about.h

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
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppAbout/Licence.txt
