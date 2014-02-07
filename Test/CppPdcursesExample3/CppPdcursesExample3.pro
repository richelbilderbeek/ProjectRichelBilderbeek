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

include(../../Libraries/Pdcurses.pri) #Or use the code below
# win32 {
#   INCLUDEPATH += \
#       ../../Libraries/pdc25_vc_w32
#
#   HEADERS += \
#       ../../Libraries/pdc25_vc_w32/panel.h \
#       ../../Libraries/pdc25_vc_w32/curses.h
#
#   LIBS += -L../../Libraries/pdc25_vc_w32 -lpdcurses
# }

SOURCES += main.cpp

