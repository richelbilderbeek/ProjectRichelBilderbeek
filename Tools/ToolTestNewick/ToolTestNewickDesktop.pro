QT       += core gui
LIBS += -lboost_program_options
TEMPLATE = app
DEFINES += NDEBUG NTRACE_BILDERBIKKEL
#Use C++0x standard
QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppBinaryNewickVector \
    ../../Classes/CppManyDigitNewick \
    ../../Classes/CppMultiVector \
    ../../Classes/CppNewick \
    ../../Classes/CppNewickRavindran \
    ../../Classes/CppNewickVector \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppSortedBinaryNewickVector \
    ../../Classes/CppTrace \
    ../../Classes/CppTwoDigitNewick \
    ../../Libraries/bigint-2010.04.30
SOURCES += \
    qtmain.cpp\
    qttestnewickdialog.cpp \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.cpp \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.cpp \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewick.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.cpp \
    ../../Classes/CppNewickRavindran/newickravindransort.cpp \
    ../../Classes/CppNewickRavindran/newickravindrancalculate.cpp \
    ../../Classes/CppNewickRavindran/newickravindran.cpp \
    ../../Classes/CppNewickVector/newickvector.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.cpp \
    testnewick.cpp \
    testnewickdialog.cpp \
    testnewickresult.cpp
HEADERS  += \
    qttestnewickdialog.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.h \
    ../../Libraries/bigint-2010.04.30/NumberlikeArray.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerLibrary.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.hh \
    ../../Libraries/bigint-2010.04.30/BigInteger.hh \
    ../../Classes/CppNewick/newickstorage.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.h \
    ../../Classes/CppManyDigitNewick/manydigitnewick.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.h \
    ../../Classes/CppNewickRavindran/newickravindran.h \
    ../../Classes/CppNewickVector/newickvector.h \
    ../../Classes/CppMultiVector/multivector.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAssert/assert.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.h \
    testnewick.h \
    testnewickdialog.h \
    testnewickresult.h
FORMS += \
    qttestnewickdialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

OTHER_FILES += \
    ../../Classes/CppManyDigitNewick/manydigitnewickalgorithm.txt
