CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

SOURCES += main.cpp

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
