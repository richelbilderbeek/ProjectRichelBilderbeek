unix {
  exists(/usr/include/qwt-qt4) {
    message(Linux: Qwt: use qwt-qt4)
    INCLUDEPATH += /usr/include/qwt-qt4
    #LIBS += -lqwt-qt4
    LIBS += -lqwt
  }

  exists(/usr/include/qwt) {
    message(Linux: Qwt: link to qwt)
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

}


unix {
  INCLUDEPATH += /usr/include/qwt
  LIBS += -lqwt
}

win32 {
  message(Windows: Qwt: link dynamically)
  INCLUDEPATH += ../../Libraries/qwt-6.1/src
  LIBS+= -L../../Libraries/qwt-6.1/lib

  CONFIG(release, debug|release) {
    message(Windows: Qwt: Linking to qwt)
    LIBS += -lqwt
  }

  CONFIG(debug, debug|release) {
    message(Windows: Qwt: Linking to qwtd)
    LIBS += -lqwtd
  }
}

