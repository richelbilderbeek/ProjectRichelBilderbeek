QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

message(Windows dynamic link to Boost)

INCLUDEPATH += \
  ../../Libraries/boost_1_54_0

debug {
  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-d-1_54.a
  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-d-1_54.a
  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-d-1_54.a
}

release {
  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-1_54.a
  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-1_54.a
  LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-1_54.a
}
