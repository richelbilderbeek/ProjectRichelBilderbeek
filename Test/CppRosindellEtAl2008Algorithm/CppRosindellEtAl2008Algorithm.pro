include(../../Libraries/Boost.pri)
include(../../Libraries/GeneralConsole.pri)


TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
    tree.cpp \
    nrrand.cpp \
    simulation.cpp \
    task.cpp \
    result.cpp \
    simulation_test.cpp \
    main.cpp \
    rng.cpp \
    treedatapoint.cpp \
    treenode.cpp

QMAKE_CXXFLAGS += -std=c++1y # -Wall -Wextra -Werror

LIBS += -lboost_filesystem -lboost_system

HEADERS += \
    tree.h \
    nrrand.h \
    simulation.h \
    task.h \
    result.h \
    rng.h \
    treedatapoint.h \
    treenode.h
