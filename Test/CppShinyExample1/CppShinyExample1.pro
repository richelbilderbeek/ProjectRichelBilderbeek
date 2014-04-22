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

include(../../Libraries/Shiny.pri) #Or use the code below
# INCLUDEPATH += \
#     ../../Libraries/Shiny/include
#
# SOURCES += \
#     ../../Libraries/Shiny/src/ShinyTools.cpp \
#     ../../Libraries/Shiny/src/ShinyOutput.cpp \
#     ../../Libraries/Shiny/src/ShinyNodePool.cpp \
#     ../../Libraries/Shiny/src/ShinyNode.cpp \
#     ../../Libraries/Shiny/src/ShinyManager.cpp
#
# HEADERS += \
#     ../../Libraries/Shiny/include/ShinyZone.h \
#     ../../Libraries/Shiny/include/ShinyTools.h \
#     ../../Libraries/Shiny/include/ShinyPrereqs.h \
#     ../../Libraries/Shiny/include/ShinyOutput.h \
#     ../../Libraries/Shiny/include/ShinyNodePool.h \
#     ../../Libraries/Shiny/include/ShinyNode.h \
#     ../../Libraries/Shiny/include/ShinyManager.h \
#     ../../Libraries/Shiny/include/ShinyMacros.h \
#     ../../Libraries/Shiny/include/ShinyData.h \
#     ../../Libraries/Shiny/include/ShinyConfig.h \
#     ../../Libraries/Shiny/include/Shiny.h


SOURCES += main.cpp

