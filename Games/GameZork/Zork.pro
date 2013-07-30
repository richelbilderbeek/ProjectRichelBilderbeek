QT -= gui
CONFIG += console
CONFIG -= app_bundle -qt
LIBS += -L/usr/lib -lcurses -ltermcap

TEMPLATE = app
QMAKE_CC = gcc
QMAKE_CCFLAGS = -x c

#Compile to C code: 'i486-linux-gnu-gcc -x c' denotes: compile C code
QMAKE_CXX = gcc
QMAKE_CXXFLAGS = -x c

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
