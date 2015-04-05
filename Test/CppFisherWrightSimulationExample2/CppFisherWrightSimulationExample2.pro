include(../../ConsoleApplication.pri)
include(../../Libraries/BoostAll.pri)
include(../../Classes/CppNewickUtils/CppNewickUtils.pri)
include(../../Classes/CppPedigree/CppPedigree.pri)

SOURCES += \
    main.cpp \
    parameters.cpp \
    simulation.cpp \
    individual.cpp \
    helper.cpp \
    sequence.cpp \
    dna.cpp \
    individual_test.cpp \
    generation.cpp


HEADERS += \
    parameters.h \
    simulation.h \
    individual.h \
    helper.h \
    sequence.h \
    dna.h \
    generation.h
