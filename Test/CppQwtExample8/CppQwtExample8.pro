#Qwt does not go together with Qwt
include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Qwt.pri)

SOURCES += main.cpp \
    myplot.cpp \
    mydialog.cpp \
    myzoomer.cpp \
    mydata.cpp \
    mycolormap.cpp

HEADERS += \
    myplot.h \
    mydialog.h \
    myzoomer.h \
    mydata.h \
    mycolormap.h

FORMS += \
    mydialog.ui
