LIBS += /home/frode/Sync/Source/Urho3D/lib/libUrho3D.a \
    -lpthread \
    -lSDL \
    -ldl \
    -lGL

DEFINES += URHO3D_COMPILE_QT

#QMAKE_CXXFLAGS += -std=c++11



INCLUDEPATH += \
    /home/frode/Sync/Source/Urho3D/include \
    /home/frode/Sync/Source/Urho3D/include/Urho3D/ThirdParty \
    #/home/frode/Sync/Source/Urho3D/Source/Samples

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

#/home/frode/Sync/Source/Urho3D/Source/Samples/29_SoundSynthesis/SoundSynthesis.h
#/home/frode/Sync/Source/Urho3D/Source/Samples/36_Urho2DTileMap/Urho2DTileMap.h
    #poolobject.h \
    #objectpool.h \
    #poolmaster.h \
