include(../../ConsoleApplicationNoWeffcpp.pri)
include(../../Libraries/GeneralConsole.pri)
include(ToolRosindellEtAl2008Console.pri)

include(../../Libraries/Urho3d.pri)

LIBS += \
    -lpthread \
    -lSDL2 \ #Otherwise use -lSDL
    -ldl \
    -lGL

SOURCES += \
    mastercontrol.cpp \
    inputmaster.cpp \
    cameramaster.cpp

HEADERS += \
    mastercontrol.h \
    inputmaster.h \
    cameramaster.h

RESOURCES += \
    ToolRosindellEtAl2008.qrc
