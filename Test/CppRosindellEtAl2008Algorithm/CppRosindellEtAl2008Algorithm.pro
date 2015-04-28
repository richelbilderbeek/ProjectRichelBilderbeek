include(../../Libraries/BoostAll.pri)
include(../../Libraries/GeneralConsole.pri)
include(../../ConsoleApplicationNoWeffcpp.pri)

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
    treenode.cpp \
    task_test.cpp \
    dispersalkernel.cpp

#QMAKE_CXXFLAGS += -std=c++1y # -Wall -Wextra -Werror

#LIBS += -lboost_filesystem -lboost_system

HEADERS += \
    tree.h \
    nrrand.h \
    simulation.h \
    task.h \
    result.h \
    rng.h \
    treedatapoint.h \
    treenode.h \
    dispersalkernel.h
