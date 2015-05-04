exists(../../Libraries) {
  message("Console application, built for Windows")
}

INCLUDEPATH += \
    ../../Libraries/Urho3D/include \
    ../../Libraries/Urho3D/Source/ThirdParty

LIBS += \
  ../../Libraries/Urho3d/Source/Urho3D/lib/libUrho3D.a

