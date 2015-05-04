include(../../ConsoleApplicationNoWeffcpp.pri)

include(../../Libraries/Urho3d.pri)

LIBS += \
    -lpthread \
    -lSDL2 \ #Otherwise use -lSDL
    -ldl \
    -lGL

# DEFINES += URHO3D_COMPILE_QT

#TEMPLATE = app
#CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += \
    mastercontrol.cpp \
    oneirocam.cpp \
    inputmaster.cpp

HEADERS += \
    mastercontrol.h \
    oneirocam.h \
    inputmaster.h
