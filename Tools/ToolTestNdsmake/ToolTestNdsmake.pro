TEMPLATE = app
OTHER_FILES +=
SOURCES += main.cpp

INCLUDEPATH += /home/richel/devkitPro/libnds/include
INCLUDEPATH += /home/richel/devkitPro/devkitARM/arm-none-eabi/include
LIBS += -L/home/richel/devkitPro/devkitARM/arm-none-eabi/lib -lstdc++
LIBS += -L/home/richel/devkitPro/libnds/lib -lnds9 -lmm9 -lfat -lfilesystem -ldswifi9


#INCLUDEPATH += /opt/devkitpro/libnds-1.4.7/include
#INCLUDEPATH += /opt/devkitpro/libnds-src-1.4.7/include/nds
#INCLUDEPATH += /opt/devkitpro/devkitARM/arm-eabi/include
#LIBS += -L/opt/devkitpro/libnds-1.4.7/lib -lnds9
#LIBS += -L/opt/devkitpro/devkitARM/arm-eabi/lib -lstdc++
DEFINES += ARM9
CONFIG   += console
CONFIG -= qt
CONFIG   -= app_bundle
TEMPLATE = app
#QMAKE_CC = /opt/devkitpro/devkitARM/bin/arm-eabi-g++
#QMAKE_CXX = /opt/devkitpro/devkitARM/bin/arm-eabi-g++
#QMAKE_LINK = /opt/devkitpro/devkitARM/bin/arm-eabi-g++
#QMAKE_LFLAGS = -T/opt/devkitpro/devkitARM/arm-eabi/lib/ds_arm9.ld

QMAKE_CC  = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-gcc
QMAKE_CXX = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++
QMAKE_CXXFLAGS = -MMD -MP -MF -mm -g -mthumb -mthumb-interwork
QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++
QMAKE_LFLAGS = -T/home/richel/devkitPro/devkitARM/arm-none-eabi/lib/ds_arm9.ld
QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-gcc
