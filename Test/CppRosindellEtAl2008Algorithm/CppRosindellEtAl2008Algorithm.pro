include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)


TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
    randomwrap.cpp \
    array1d.cpp \
    tree.cpp \
    nrrand.cpp \
    array2d.cpp \
    simulation.cpp \
    task.cpp \
    result.cpp \
    simulation_test.cpp \
    main.cpp \
    rng.cpp

QMAKE_CXXFLAGS += -std=c++1y # -Wall -Wextra -Werror

LIBS += -lboost_filesystem -lboost_system

HEADERS += \
    randomwrap.h \
    array1d.h \
    tree.h \
    nrrand.h \
    array2d.h \
    globals.h \
    simulation.h \
    task.h \
    result.h \
    rng.h
