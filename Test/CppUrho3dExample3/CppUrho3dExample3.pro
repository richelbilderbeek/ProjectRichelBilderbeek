include(../../Libraries/Urho3D/Urho3d.pri)

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
  ../../Libraries/Urho3D/Source/Samples/03_Sprites/Sprites.cpp

HEADERS += \
  ../../Libraries/Urho3D/Source/Samples/03_Sprites/Sprites.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

