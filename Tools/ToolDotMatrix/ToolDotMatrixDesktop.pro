QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToolDotMatrix
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    tooldotmatrixmenudialog.cpp \
    qttooldotmatrixmaindialog.cpp \
    qttooldotmatrixmenudialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    dotmatrix.cpp

HEADERS  += \
    tooldotmatrixmenudialog.h \
    qttooldotmatrixmaindialog.h \
    qttooldotmatrixmenudialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    dotmatrix.h

FORMS    += \
    qttooldotmatrixmaindialog.ui \
    qttooldotmatrixmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

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

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../ToolDotMatrixVcl/UnitFormDotMatrix.dfm \
    ../ToolDotMatrixVcl/UnitFormDotMatrix.ddp \
    ../ToolDotMatrixVcl/UnitFormAbout.dfm \
    ../ToolDotMatrixVcl/UnitFormAbout.ddp
