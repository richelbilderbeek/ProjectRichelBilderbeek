TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    main_2.cpp \
    BasicDemo.cpp \
    Win32BasicDemo.cpp

DEFINES += B3_USE_CLEW
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra #-Weffc++ -Werror

INCLUDEPATH += \
  ../../Libraries/bullet3/src \
  ../../Libraries/bullet3/btgui

HEADERS += \
    BasicDemo.h
