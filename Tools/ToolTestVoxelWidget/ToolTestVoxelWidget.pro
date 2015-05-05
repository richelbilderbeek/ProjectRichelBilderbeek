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
    inputmaster.cpp \
    cameramaster.cpp

HEADERS += \
    mastercontrol.h \
    inputmaster.h \
    cameramaster.h

RESOURCES += \
    ToolTestVoxelWidget.qrc
