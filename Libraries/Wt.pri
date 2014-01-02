unix {
  INCLUDEPATH += \
    ../../Libraries/wt/src
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/wt-3.3.1/src
}

unix {
  LIBS += -lwt -lwthttp
}
