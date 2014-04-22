win32 {
  # Windows only
  message("Qwt 6.1, built for Windows")
  INCLUDEPATH += ../../Libraries/qwt-6.1/src
  LIBS+= -L../../Libraries/qwt-6.1/lib

  CONFIG(release, debug|release) {
    message("Qwt 6.1, built for Windows, release")
    LIBS += -lqwt
  }

  CONFIG(debug, debug|release) {
    message("Qwt 6.1, built for Windows, debug")
    LIBS += -lqwtd
  }
}

macx {
  # Mac only
  message("Qwt 6.1, built for Mac")
}

unix:!macx{
  # Linux only
  message("Qwt 6.1, built for Linux")

  exists(/usr/include/qwt-qt4) {
    message("Qwt 6.1, built for Linux, use qwt-qt4")
    INCLUDEPATH += /usr/include/qwt-qt4
    #LIBS += -lqwt-qt4
    LIBS += -lqwt
  }

  exists(/usr/include/qwt) {
    message("Qwt 6.1, built for Linux, use qwt")
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

  INCLUDEPATH += /usr/include/qwt
  LIBS += -lqwt
}

cross_compile {
  # Crosscompile only
  message("Qwt 6.1, cross-compiling from Linux to Windows")
}
