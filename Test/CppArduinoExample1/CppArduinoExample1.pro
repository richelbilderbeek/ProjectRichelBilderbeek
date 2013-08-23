TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../Libraries/Arduino/hardware/arduino/cores/arduino

SOURCES += \
    mymain.cpp \
    ../../Libraries/Arduino/hardware/arduino/cores/main.cpp


