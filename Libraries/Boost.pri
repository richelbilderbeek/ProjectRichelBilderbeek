win32 {
  # Windows only
  message("Boost, built for Windows")
  INCLUDEPATH += \
    ../../Libraries/boost_1_56_0
}

macx {
  # Mac only
  message("Boost, built for Mac")
  INCLUDEPATH += \
    ../../Libraries/boost_1_56_0
}

unix:!macx {
  # Linux only
  message("Boost, built for Linux")
}

cross_compile {
  # Crosscompile only
  message("Boost, built for cross-compiling from Linux to Windows")
}
