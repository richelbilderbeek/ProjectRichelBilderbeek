include(../../Libraries/Urho3d.pri)

LIBS += \
     #/home/frode/Sync/Source/Urho3D/lib/libUrho3D.a \
    -lpthread \
    -lSDL2 \ #Otherwise use -lSDL
    -ldl \
    -lGL

DEFINES += URHO3D_COMPILE_QT

QMAKE_CXXFLAGS += -std=c++1y



#INCLUDEPATH += \
#    /home/frode/Sync/Source/Urho3D/include \
#    /home/frode/Sync/Source/Urho3D/include/Urho3D/ThirdParty \

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    mastercontrol.cpp \
    oneirocam.cpp \
    inputmaster.cpp

HEADERS += \
    mastercontrol.h \
    oneirocam.h \
    inputmaster.h
