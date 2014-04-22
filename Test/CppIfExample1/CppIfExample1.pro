TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ 
unix {
  QMAKE_CXXFLAGS += -Werror
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}


