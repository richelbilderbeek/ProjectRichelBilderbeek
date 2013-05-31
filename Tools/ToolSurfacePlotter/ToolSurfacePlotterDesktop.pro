QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x
TARGET = ToolSurfacePlotterDesktop
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppSurfacePlotter \
    ../../Classes/CppSurfacePlotterWidget \
    ../../Classes/CppQtAboutDialog \
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
    ../../Libraries/fparser4.4.3/fpoptimizer.cc \
    ../../Libraries/fparser4.4.3/fparser.cc

HEADERS  += qttoolsurfaceplottermenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    toolsurfaceplottermenudialog.h \
    qttoolsurfaceplottermaindialog.h \
    ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h \
    ../../Libraries/fparser4.4.3/fpconfig.hh \
    ../../Libraries/fparser4.4.3/fparser_mpfr.hh \
    ../../Libraries/fparser4.4.3/fparser_gmpint.hh \
    ../../Libraries/fparser4.4.3/fparser.hh \
    ../../Libraries/fparser4.4.3/extrasrc/fptypes.hh \
    ../../Libraries/fparser4.4.3/extrasrc/fpaux.hh

FORMS    += qttoolsurfaceplottermenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttoolsurfaceplottermaindialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtSurfacePlotWidget/Licence.txt \
    ../../Libraries/fparser4.4.3/extrasrc/fp_opcode_add.inc \
    ../../Libraries/fparser4.4.3/extrasrc/fp_identifier_parser.inc

RESOURCES += \
    ToolSurfacePlotter.qrc
