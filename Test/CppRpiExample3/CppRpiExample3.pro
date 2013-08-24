TEMPLATE = app
CONFIG += console
CONFIG -= qt
#QMAKE_CXXFLAGS += -std=c++0x

#QMAKE_CXX = gcc
#QMAKE_CXXFLAGS = -x c

INCLUDEPATH += \
    ../../Libraries/Arduino/hardware/arduino/cores/arduino \
    ../../Libraries/Arduino/hardware/arduino/variants/standard \
    ../../Libraries/avr-libc-1.8.0/include


SOURCES += \
    ../../Libraries/Arduino/hardware/arduino/cores/arduino/main.cpp \
    mymain.cpp \
    ../../Libraries/Arduino/hardware/arduino/cores/arduino/wiring_digital.c
