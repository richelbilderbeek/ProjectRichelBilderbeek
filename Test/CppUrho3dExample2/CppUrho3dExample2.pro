include(../../Libraries/Urho3d.pri)

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
  ../../Libraries/Urho3D/Source/Samples/02_HelloGUI/HelloGUI.cpp

HEADERS += \
  ../../Libraries/Urho3D/Source/Samples/02_HelloGUI/HelloGUI.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

