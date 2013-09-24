QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppGaborFilter \
    ../../Classes/CppGaborFilterWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtGaborFilterWidget \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtSurfacePlotWidget \
    ../../Classes/CppRectangle \
    ../../Classes/CppWidget

SOURCES += qtmain.cpp \
        qttoolgaborfiltermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    toolgaborfiltermenudialog.cpp \
    qttoolgaborfiltermaindialog.cpp \
    ../../Classes/CppGaborFilter/gaborfilter.cpp \
    ../../Classes/CppGaborFilterWidget/gaborfilterwidget.cpp \
    ../../Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += qttoolgaborfiltermenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    toolgaborfiltermenudialog.h \
    qttoolgaborfiltermaindialog.h \
    ../../Classes/CppGaborFilter/gaborfilter.h \
    ../../Classes/CppGaborFilterWidget/gaborfilterwidget.h \
    ../../Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS    += qttoolgaborfiltermenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttoolgaborfiltermaindialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppGaborFilter/Licence.txt \
    ../../Classes/CppGaborFilterWidget/Licence.txt \
    ../../Classes/CppQtGaborFilterWidget/Licence.txt \
    ../../Classes/CppWidget/Licence.txt \
    ../../Classes/CppRectangle/Licence.txt \
    ../../Classes/CppQtSurfacePlotWidget/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

RESOURCES += \
    ToolGaborFilter.qrc

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
