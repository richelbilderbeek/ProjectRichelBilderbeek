message("Compiling this will fail, use the Makefile instead")

INCLUDEPATH += /home/richel/devkitPro/libnds/include
INCLUDEPATH += /home/richel/devkitPro/devkitARM/arm-none-eabi/include
LIBS += -L/home/richel/devkitPro/devkitARM/arm-none-eabi/lib -lstdc++
LIBS += -L/home/richel/devkitPro/libnds/lib -lnds9 -lmm9 -lfat -lfilesystem -ldswifi9
DEFINES += ARM9
CONFIG   += console
CONFIG -= qt
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
QMAKE_CC  = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-gcc
QMAKE_CXX = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++
QMAKE_CXXFLAGS = -MMD -MP -MF -mm -g -mthumb -mthumb-interwork
QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++
QMAKE_LFLAGS = -T/home/richel/devkitPro/devkitARM/arm-none-eabi/lib/ds_arm9.ld
QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-gcc
