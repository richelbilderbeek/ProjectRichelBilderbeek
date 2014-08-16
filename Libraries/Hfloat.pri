win32 {
  # Windows only
  message("HFLOAT, built for Windows")

  INCLUDEPATH += \
      ../../Libraries/hfloat/src/include


  HEADERS += \
    ../../Libraries/hfloat/src/include/types.h \
    ../../Libraries/hfloat/src/include/hfverbosity.h \
    ../../Libraries/hfloat/src/include/hfloatop.h \
    ../../Libraries/hfloat/src/include/hfloatfu.h \
    ../../Libraries/hfloat/src/include/hfloat.h \
    ../../Libraries/hfloat/src/include/hfdatafu.h \
    ../../Libraries/hfloat/src/include/hfdata.h



}

macx {
  # Mac only
  message("HFLOAT, built for Mac")
  error("?HFLOAT does not work under Mac")
}

unix:!macx {
  # Linux only
  message("HFLOAT, built for Linux")
}

cross_compile {
  # Crosscompile only
  message("HFLOAT, built for cross-compiling from Linux to Windows")
  error("?HFLOAT does not cross-compile from Linux to Windows")
}

