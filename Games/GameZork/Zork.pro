#-------------------------------------------------
#
# Project created by QtCreator 2010-05-02T08:31:54
#
#-------------------------------------------------
# -spec linux-pgcc
QT -= gui
TARGET = Zork
CONFIG += console
CONFIG -= app_bundle -qt
#LIBS += -L/usr/lib -lstdc++
#LIBS += -L/usr/lib -lc
LIBS += -L/usr/lib -lcurses -ltermcap
#LIBS++ -L/usr/lib/gcc/i686-linux-gnu/4.4 -lgcc

TEMPLATE = app
#QMAKE_CC = i486-linux-gnu-gcc
QMAKE_CC = gcc
QMAKE_CCFLAGS = -x c

#Compile to C code: 'i486-linux-gnu-gcc -x c' denotes: compile C code
#QMAKE_CXX = i486-linux-gnu-gcc
#QMAKE_CXXFLAGS = -x c

#Compile to C code: 'i486-linux-gnu-gcc -x c' denotes: compile C code
QMAKE_CXX = gcc
QMAKE_CXXFLAGS = -x c


#QMAKE_CXX = gcc
#QMAKE_CC = gcc
#QMAKE_MAKESPECS = linux-gcc
HEADERS += \
    VARS.H \
    PARSE.H \
    parse.h \
    vars.h \
    funcs.h
SOURCES += \
    DMAIN.C \
    VERBS.C \
    VILLNS.C \
    SOBJS.C \
    SVERBS.C \
    ROOMS.C \
    OBJCTS.C \
    NP3.C \
    NROOMS.C \
    NP2.C \
    NP1.C \
    NP.C \
    NOBJS.C \
    LIGHTP.C \
    LOCAL.C \
    GDT.C \
    DVERB1.C \
    DVERB2.C \
    DSUB.C \
    DSO7.C \
    DSO6.C \
    DSO5.C \
    DSO4.C \
    DSO3.C \
    DSO2.C \
    DEMONS.C \
    DSO1.C \
    DINIT.C \
    DGAME.C \
    ACTORS.C \
    CLOCKR.C \
    BALLOP.C \
    SUPP.C
