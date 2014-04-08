exists(../../WebApplication.pri) {
  include(../../WebApplication.pri)
}
!exists(../../WebApplication.pri) {
  QT       += core
  QT       -= gui
  CONFIG   += console
  CONFIG   -= app_bundle
  TEMPLATE = app
}

exists(../../Libraries/BoostAll.pri) {
  include(../../Libraries/BoostAll.pri)
}
!exists(../../Libraries/BoostAll.pri) {
  INCLUDEPATH += \
    ../../Libraries/boost_1_55_0
  LIBS += \
    -lboost_date_time \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_signals \
    -lboost_system
}

exists(../../Libraries/Wt.pri) {
  include(../../Libraries/Wt.pri)
}
!exists(../../Libraries/Wt.pri) {
  INCLUDEPATH += \
    ../../Libraries/wt/src \
    ../../Libraries/wt/build
  LIBS += -lwt -lwthttp
}

SOURCES += main.cpp
