#DEFINES += FIX_ISSUE_168
#DEFINES += ANSI_DECLARATORS
QMAKE_CXXFLAGS += -Werror

exists(../../ConsoleApplication.pri) {
  include(../../ConsoleApplication.pri)
}
!exists(../../ConsoleApplication.pri) {
  QT += core
  QT += gui
  greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
  CONFIG   += console
  CONFIG   -= app_bundle
  TEMPLATE = app
  CONFIG(release, debug|release) {
    DEFINES += NDEBUG NTRACE_BILDERBIKKEL
  }
  QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++
  unix {
    QMAKE_CXXFLAGS += -Werror
  }
}

exists(../../Libraries/Boost.pri) {
  include(../../Libraries/Boost.pri)
}
!exists(../../Libraries/Boost.pri) {
  win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
  }
}

include(../../Libraries/GeneralConsole.pri)

include(../../Classes/CppChess/CppChess.pri)
include(../../Classes/CppChessResources/CppChessResources.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Tools/ToolTestChess/ToolTestChessConsole.pri)

SOURCES += main.cpp
