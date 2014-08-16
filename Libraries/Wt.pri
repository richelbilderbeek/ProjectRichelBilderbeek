win32 {
  # Windows only
  message("Wt, built for Windows")
  INCLUDEPATH += \
    ../../Libraries/wt/src \
    ../../Libraries/wt/build
  LIBS += \
    -L/../../Libraries/wt/src
}

macx {
  # Mac only
  message("Wt, built for Mac")
  INCLUDEPATH += \
    ../../Libraries/wt/src
  LIBS += -lwt -lwthttp
}

unix:!macx{
  # Linux only
  message("Wt, built for Linux")
  #INCLUDEPATH += \
  #  ../../Libraries/wt/src
  LIBS += -lwt -lwthttp
}

cross_compile {
  # Crosscompile only
  message("Wt, cross-compiling from Linux to Windows")
  INCLUDEPATH += \
    ../../Libraries/wt/src
  LIBS += -lwt -lwthttp
}

