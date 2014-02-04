include(../../ConsoleApplication.pri) #Or use the code below
# QT += core
# QT += gui
# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# CONFIG   += console
# CONFIG   -= app_bundle
# TEMPLATE = app
# CONFIG(release, debug|release) {
#   DEFINES += NDEBUG NTRACE_BILDERBIKKEL
# }
# QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++
# unix {
#   QMAKE_CXXFLAGS += -Werror
# }

include(../../Libraries/Boost.pri) #Or use the code below
# win32 {
#   INCLUDEPATH += \
#     ../../Libraries/boost_1_54_0
# }

SOURCES += main.cpp

#
#
# gmtl
#
#

unix {
  message(Unix: gmtl: not tested)
}

win32 {
  message(Windows: gmtl: include path)
  INCLUDEPATH+= ../../Libraries/gmtl-0.6.1
}
