QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppGaborFilter \
    ../../Classes/CppGaborFilterWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtGaborFilterWidget \
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
    ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.cpp

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
    ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h

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
    ../../Classes/CppQtSurfacePlotWidget/Licence.txt

RESOURCES += \
    ToolGaborFilter.qrc
