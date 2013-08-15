TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp

win32 {

  message(Windows: add Boost to includepath)

  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}


