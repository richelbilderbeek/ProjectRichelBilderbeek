TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

include(../../Classes/CppDnaSequence/CppDnaSequence.pri)
include(../../Classes/CppBeast/CppBeast.pri)
include(../../Classes/CppFastaFile/CppFastaFile.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppTrace/CppTrace.pri)
include(../../Classes/CppTestTimer/CppTestTimer.pri)

SOURCES += \
    main.cpp \
    parameters.cpp \
    simulation.cpp \
    individual.cpp \
    helper.cpp


QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Werror

LIBS += -lboost_filesystem -lboost_system

HEADERS += \
    parameters.h \
    simulation.h \
    individual.h \
    helper.h

RESOURCES += \
    Beaster.qrc
