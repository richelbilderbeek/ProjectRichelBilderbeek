TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

# Use C++11 to prevent:
# error: 'round' is not a member of 'std'
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
