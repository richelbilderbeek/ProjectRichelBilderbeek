include(../../DesktopApplication.pri) #Or use the code below
#
# QT       += core gui
# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#
# win32 {
#   greaterThan(QT_MAJOR_VERSION, 4): QT += svg
# }
#
# TEMPLATE = app
#
# CONFIG(debug, debug|release) {
#   message(Debug mode)
# }
#
# CONFIG(release, debug|release) {
#   message(Release mode)
#   DEFINES += NDEBUG NTRACE_BILDERBIKKEL
# }
#
# QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++
#
# unix {
#   QMAKE_CXXFLAGS += -Werror
# }


SOURCES += main.cpp \
           dialog.cpp
HEADERS  += dialog.h
FORMS    += dialog.ui
