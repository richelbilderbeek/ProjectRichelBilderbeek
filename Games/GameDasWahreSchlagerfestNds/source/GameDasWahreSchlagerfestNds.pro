message("Compiling this may fail")
message("Compiling this will fail, use the Makefile instead")

INCLUDEPATH += \
    ../../../Games/GameDasWahreSchlagerfest

SOURCES += \
    ../../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.cpp \
    ../../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestdisplay.cpp

HEADERS  += \
    ndsgamedialog.h \
    ../../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.h \
    ../../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestdisplay.h \
    picbeer.h \
    picbratwurst.h \
    picempty.h

OTHER_FILES += \
    ../../../Games/GameDasWahreSchlagerfest/Licence.txt

INCLUDEPATH += /home/richel/devkitPro/libnds/include
INCLUDEPATH += /home/richel/devkitPro/devkitARM/arm-none-eabi/include
INCLUDEPATH += ../build
LIBS += -L/home/richel/devkitPro/devkitARM/arm-none-eabi/lib -lstdc++ -lm
LIBS += -L/home/richel/devkitPro/libnds/lib -lnds9 -lmm9 -ldswifi9
DEFINES += ARM9 NDEBUG
CONFIG   += console
CONFIG -= qt
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    ndsgamedialog.cpp
QMAKE_CC  = /home/richel/devkitPr o/devkitARM/bin/arm-none-eabi-gcc
QMAKE_CXX = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++
QMAKE_CXXFLAGS = -MMD -MP -MF -mm -g -mthumb -mthumb-interwork -std=c++14
QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++
QMAKE_LFLAGS = -T/home/richel/devkitPro/devkitARM/arm-none-eabi/lib/ds_arm9.ld

QMAKE_LINK = /home/richel/devkitPro/devkitARM/bin/arm-none-eabi-gcc

