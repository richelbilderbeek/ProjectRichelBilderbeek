QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    createqtprojectzipfilemenudialog.cpp \
    createqtprojectzipfilepath.cpp \
    main.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppTrace/trace.h \
    createqtprojectzipfilemenudialog.h \
    createqtprojectzipfilepath.h

OTHER_FILES += \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtCreatorProFile/Licence.txt

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
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_system
}

