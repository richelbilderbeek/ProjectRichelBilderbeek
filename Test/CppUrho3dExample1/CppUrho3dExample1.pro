include(../../Libraries/Urho3D/Urho3d.pri)

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
  ../../Libraries/Urho3D/Source/Samples/01_HelloWorld/HelloWorld.cpp

HEADERS += \
  ../../Libraries/Urho3D/Source/Samples/01_HelloWorld/HelloWorld.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
