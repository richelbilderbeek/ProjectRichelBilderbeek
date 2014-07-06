#Qwt does not go together with Qwt
include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Qwt.pri)

SOURCES += main.cpp \
    qtwidget.cpp \
    qwtplotitem.cpp \
    qwtplotwidget.cpp \
    qttextitem.cpp

HEADERS += \
    qtwidget.h \
    qwtplotitem.h \
    qwtplotwidget.h \
    qttextitem.h

