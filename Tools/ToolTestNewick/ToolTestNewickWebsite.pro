QT       += core gui
LIBS += -lwt -lwthttp -lboost_program_options
TEMPLATE = app
#Use C++0x standard
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -DNDEBUG
DEFINES += USE_WT_LIBRARY
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppBinaryNewickVector \
    ../../Classes/CppEncranger \
    ../../Classes/CppLoopReader \
    ../../Classes/CppManyDigitNewick \
    ../../Classes/CppMultiVector \
    ../../Classes/CppNewick \
    ../../Classes/CppNewickRavindran \
    ../../Classes/CppNewickVector \
    ../../Classes/CppSortedBinaryNewickVector \
    ../../Classes/CppTrace \
    ../../Classes/CppTwoDigitNewick \
    ../../Classes/CppWtAboutDialog \
    ../../Libraries/bigint-2010.04.30
SOURCES += wtmain.cpp\
    wttestnewickdialog.cpp \
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
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppEncranger/encranger.cpp \
    testnewick.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.cpp \
    testnewickdialog.cpp
HEADERS  += \
    wttestnewickdialog.h \
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
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppLoopReader/loopreader.h \
    testnewick.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.h \
    testnewickdialog.h

OTHER_FILES += \
    wt.css
