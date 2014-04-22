include(../../DesktopApplication.pri) #Or use the code below
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
# QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -Weffc++
# unix {
#   QMAKE_CXXFLAGS += -Werror
# }

include(../../Libraries/Boost.pri) #Or use the code below
# win32 {
#   INCLUDEPATH += \
#     ../../Libraries/boost_1_54_0
# }

include(../../Libraries/Poppler.pri) #Or use the code below
# unix {
#   LIBS += -L/usr/local/bin -lpoppler-qt4
# }

QT       += core gui xml
SOURCES += main.cpp \
        dialogmain.cpp
HEADERS  += dialogmain.h
FORMS    += dialogmain.ui
RESOURCES += resources.qrc
