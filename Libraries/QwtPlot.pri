#
#
# Qwt
#
#

unix {

  exists(/usr/include/qwt-qt4) {
    message(Linux: Qwt: use qwt-qt4)
    INCLUDEPATH += /usr/include/qwt-qt4
    LIBS += -lqwt-qt4
  }

  exists(/usr/include/qwt) {
    message(Linux: Qwt: link to qwt)
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

}

win32 {
  exists (../../Libraries/qwt-6.0.1/src) {
    message(Windows: Qwt: 6.0.1)
    INCLUDEPATH+= ../../Libraries/qwt-6.0.1/src
  }


  exists (qwt-6.1.0/src) {
    message(Windows: Qwt: 6.1.0)
    INCLUDEPATH+= qwt-6.1.0/src
    INCLUDEPATH+= ../../Libraries/qwt-6.0.1/src
  }

  exists (../../Libraries/qwt-6.1.0/src) {
    message(Windows: Qwt: 6.1.0)
    INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
    #LIBS+= -L../../Libraries/qwt-6.1.0/lib

    #CONFIG(release, debug|release) {
    #  message(Windows: Qwt: Linking to qwt)
    #  LIBS += -lqwt
    #}

    #CONFIG(debug, debug|release) {
    #  message(Windows: Qwt: Linking to qwtd)
    #  LIBS += -lqwtd
    #}
  }
}
