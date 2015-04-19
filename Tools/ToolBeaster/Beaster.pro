TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

include(../../Classes/CppDnaSequence/CppDnaSequence.pri)
include(../../Classes/CppBeast/CppBeast.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppTrace/CppTrace.pri)
include(../../Classes/CppTestTimer/CppTestTimer.pri)

SOURCES += \
    main.cpp \
    parameters.cpp \
    simulation.cpp \
    individual.cpp \
    beastparameterfile.cpp \
    fastafile.cpp \
    helper.cpp \
#    sequence.cpp \
    rscript.cpp \
    beaststatefile.cpp


QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Werror

LIBS += -lboost_filesystem -lboost_system

HEADERS += \
    parameters.h \
    simulation.h \
    individual.h \
    beastparameterfile.h \
    fastafile.h \
    helper.h \
#    sequence.h \
    rscript.h \
    beaststatefile.h

RESOURCES += \
    Beaster.qrc
