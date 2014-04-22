QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppGaborFilter/CppGaborFilter.pri)
include(../../Classes/CppGaborFilterWidget/CppGaborFilterWidget.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppRectangle/CppRectangle.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)

include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../../Classes/CppQtGaborFilterWidget/CppQtGaborFilterWidget.pri)
include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)
include(../../Classes/CppQtSurfacePlotWidget/CppQtSurfacePlotWidget.pri)

include(../../Classes/CppTrace/CppTrace.pri)
include(../../Classes/CppWidget/CppWidget.pri)
include(../../Tools/ToolGaborFilter/ToolGaborFilterDesktop.pri)

SOURCES += qtmain.cpp


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

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
