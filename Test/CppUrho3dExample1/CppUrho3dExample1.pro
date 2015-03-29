# Add this to the constructor
#  std::system("ln -s ../../Libraries/Urho3D/bin/Data"); //RJCB
#  std::system("ln -s ../../Libraries/Urho3D/bin/CoreData"); //RJCB

# Use the line below:
#   include(../../Libraries/Urho3D/Urho3d.pri)
# But for completeness, its content is shown here:

LIBS += ../../Libraries/Urho3D/lib/libUrho3D.a

INCLUDEPATH += \
  ../../Libraries/Urho3D/include \
  ../../Libraries/Urho3D/Source/Samples

LIBS += \
  -lpthread \
  -lSDL -lSDL_image -lSDL_ttf \
  -ldl \
  -lGL

DEFINES += URHO3D_COMPILE_QT
# End of the content of ../../Libraries/Urho3D/Urho3d.pri


QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
  ../../Libraries/Urho3D/Source/Samples/01_HelloWorld/HelloWorld.cpp

HEADERS += \
  ../../Libraries/Urho3D/Source/Samples/01_HelloWorld/HelloWorld.h

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
