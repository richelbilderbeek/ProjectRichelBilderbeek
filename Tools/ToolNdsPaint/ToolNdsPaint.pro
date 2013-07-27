#-------------------------------------------------
#
# Project created by QtCreator 2010-10-13T17:10:22
#
#-------------------------------------------------
QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

#Define this flag for NDS
#NDS development (must make from command line, however)
INCLUDEPATH += /opt/devkitpro/libnds-1.4.7/include
INCLUDEPATH += /opt/devkitpro/libnds-src-1.4.7/include/nds
INCLUDEPATH += /opt/devkitpro/devkitARM/arm-eabi/include
LIBS += -L/opt/devkitpro/libnds-1.4.7/lib -lnds9
LIBS += -L/opt/devkitpro/devkitARM/arm-eabi/lib -lstdc++
DEFINES += ARM9
CONFIG   += console
CONFIG -= qt
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CC = /opt/devkitpro/devkitARM/bin/arm-eabi-g++
QMAKE_CXX = /opt/devkitpro/devkitARM/bin/arm-eabi-g++
QMAKE_LINK = /opt/devkitpro/devkitARM/bin/arm-eabi-g++
QMAKE_LFLAGS = -T/opt/devkitpro/devkitARM/arm-eabi/lib/ds_arm9.ld
