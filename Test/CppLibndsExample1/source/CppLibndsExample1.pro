INCLUDEPATH += /home/richel/devkitPro/libnds/include
INCLUDEPATH += /home/richel/devkitPro/devkitARM/arm-none-eabi/include
LIBS += -L/home/richel/devkitPro/devkitARM/arm-none-eabi/lib -lstdc++
LIBS += -L/home/richel/devkitPro/libnds/lib -lnds9

DEFINES += ARM9
CONFIG   += console
CONFIG -= qt
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

QMAKE_CC  = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-gcc
QMAKE_CXX = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++


SOURCES += /home/richel/devkitPro/libnds/source/common/interrupts.c

##QMAKE_CCFLAGS = -MMD -MP -MF -g -mthumb-interwork
##QMAKE_CXXFLAGS = -MMD -MP -MF -g -mthumb -mthumb-interwork

QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++

#I hoped this would be a golden combination:
#QMAKE_LFLAGS = -T/home/richel/devkitPro/devkitARM/arm-none-eabi/lib/ds_arm9.ld
#QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-gcc
