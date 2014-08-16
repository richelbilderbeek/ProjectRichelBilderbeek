#Qwt does not go together with Qwt
include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Qwt.pri)

SOURCES += main.cpp\
        qtdialog.cpp \
    alphabetafilter.cpp \
    alphafilter.cpp

HEADERS  += qtdialog.h \
    alphabetafilter.h \
    alphafilter.h

FORMS    += qtdialog.ui
