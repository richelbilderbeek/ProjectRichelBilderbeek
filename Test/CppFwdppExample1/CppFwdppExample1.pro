include(../../ConsoleApplicationNoWeffcpp.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Fwdpp.pri)
include(../../Libraries/Libsequence.pri)

LIBS += -lgsl
LIBS += -lgslcblas
LIBS += -lz

SOURCES += diploid.cc
HEADERS += common_gamete.hpp


# N theta rho ngens samplesize nreps seed
# 1000 1 1 1000 100 100 42
