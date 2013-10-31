QT += core
QT -= gui
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppCodeToHtml/CppCodeToHtml.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppQrcFile/CppQrcFile.pri)
include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)
include(../../Tools/ToolCodeToHtml/ToolCodeToHtmlConsole.pri)

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

unix {
  LIBS += -lboost_program_options
}

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
