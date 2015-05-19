INCLUDEPATH += \
    ../../Libraries/Urho3D/include \
    ../../Libraries/Urho3D/include/Urho3D/ThirdParty

LIBS += \
  ../../Libraries/Urho3D/lib/libUrho3D.a

LIBS += \
    -lpthread \
    -lSDL2 \ #Otherwise use -lSDL
    -ldl \
    -lGL

DEFINES += RIBI_USE_SDL_2
