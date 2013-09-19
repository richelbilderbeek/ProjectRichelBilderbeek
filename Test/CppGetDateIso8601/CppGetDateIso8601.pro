TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++ -Werror
SOURCES += main.cpp

unix {
  LIBS += -lboost_date_time
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
