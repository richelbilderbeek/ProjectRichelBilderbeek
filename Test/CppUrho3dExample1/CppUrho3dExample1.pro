# Add this to the constructor
#  std::system("ln -s ../../Libraries/Urho3D/bin/Data"); //RJCB
#  std::system("ln -s ../../Libraries/Urho3D/bin/CoreData"); //RJCB

# Use the line below:
#   include(../../Libraries/Urho3D/Urho3d.pri)
# But for completeness, its content is shown here:

include(../../ConsoleApplicationNoWeffcpp.pri)
include(../../Libraries/Urho3d.pri)


SOURCES += HelloWorld.cpp
HEADERS += HelloWorld.h
