
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


# Install STK by:
# sudo apt-get install libstk0-dev
include(../../Libraries/Stk.pri) #Or use the code below
# INCLUDEPATH += /usr/include/stk
# LIBS += -L/usr/lib -lstk -lrtaudio

SOURCES += main.cpp

