TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
  ../../Libraries/boost_1_54_0

CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}
