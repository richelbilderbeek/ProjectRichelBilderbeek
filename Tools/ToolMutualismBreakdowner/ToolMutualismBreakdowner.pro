#Qwt does not go together with Qwt
include(../../DesktopApplicationNoWeffcpp.pri)
include(../../Libraries/Qwt.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent opengl printsupport

SOURCES += \
    main.cpp \
    qtdialog.cpp \
    simulation.cpp \
    simulation_test.cpp \
    parameters.cpp

HEADERS  += qtdialog.h \
    simulation.h \
    parameters.h

FORMS    += qtdialog.ui

