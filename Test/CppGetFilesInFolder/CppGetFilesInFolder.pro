QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

QMAKE_CXXFLAGS +=  -Wall -Wextra -Werror

#
#
# Boost
#
#

unix {
  message(Unix dynamic link to Boost)

  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {

  message(Windows dynamic link to Boost)

  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  debug {
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-d-1_54.a
#    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-d-1_54.a
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-d-1_54.a
  }
  release {
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-1_54.a
#    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-1_54.a
    LIBS += e:/Projects/Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-1_54.a
  }
}
