# Add this to the constructor
#  std::system("ln -s ../../Libraries/Urho3D/bin/Data"); //RJCB
#  std::system("ln -s ../../Libraries/Urho3D/bin/CoreData"); //RJCB

include(../../ConsoleApplicationNoWeffcpp.pri)
include(../../Libraries/Urho3d.pri)


SOURCES += HelloWorld.cpp
HEADERS += HelloWorld.h
