INCLUDEPATH += \
  ../../Libraries/wt/src

unix {
  LIBS += -lwt -lwthttp
}
