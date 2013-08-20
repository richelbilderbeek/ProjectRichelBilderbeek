TEMPLATE = app
CONFIG += qt console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
SOURCES += main.cpp

win32 {
  #message(Native Windows dynamic link to Boost)
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  debug {
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-d-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-d-1_54.a
  }
  release {
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-1_54.a
  }
}

RESOURCES += \
    CppIsRegularFile.qrc
