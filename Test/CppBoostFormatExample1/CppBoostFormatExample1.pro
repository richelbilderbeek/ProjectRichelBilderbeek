TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -Werror

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
