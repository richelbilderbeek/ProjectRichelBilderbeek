QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppSurfacePlotter \
    ../../Classes/CppSurfacePlotterWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtSurfacePlotWidget \
    ../../Libraries/fparser4.4.3 \
    ../../Libraries/fparser4.4.3/extrasrc


SOURCES += qtmain.cpp \
        qttoolsurfaceplottermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    toolsurfaceplottermenudialog.cpp \
    qttoolsurfaceplottermaindialog.cpp \
    ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += qttoolsurfaceplottermenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    toolsurfaceplottermenudialog.h \
    qttoolsurfaceplottermaindialog.h \
    ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS    += qttoolsurfaceplottermenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttoolsurfaceplottermaindialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtSurfacePlotWidget/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

RESOURCES += \
    ToolSurfacePlotter.qrc


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

#
#
# Warp's function parser
#
#
#unix {
  INCLUDEPATH += \
    ../../Libraries/fparser4.5.1

  HEADERS += \
    ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
    ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
    ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
    ../../Libraries/fparser4.5.1/fparser.hh \
    ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
    ../../Libraries/fparser4.5.1/fpconfig.hh

  SOURCES += \
    ../../Libraries/fparser4.5.1/fparser.cc \
    ../../Libraries/fparser4.5.1/fpoptimizer.cc


  OTHER_FILES += \
    ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
    ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
#}
