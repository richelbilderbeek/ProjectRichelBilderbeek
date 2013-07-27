QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options

QMAKE_CXXFLAGS += -std=c++0x

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppRectangle \
    ../../Classes/CppShape \
    ../../Classes/CppShapeWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtShapeWidget

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppShape/shape.cpp \
    ../../Classes/CppShapeWidget/shapewidget.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    wttestshapemaindialog.cpp \
    wttestshapemenudialog.cpp \
    testshapemaindialog.cpp \
    testshapemenudialog.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWtShapeWidget/wtshapewidget.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppShape/shape.h \
    ../../Classes/CppShapeWidget/shapewidget.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    wttestshapemaindialog.h \
    wttestshapemenudialog.h \
    testshapemaindialog.h \
    testshapemenudialog.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppWtShapeWidget/wtshapewidget.h

RESOURCES += \
    ToolTestShape.qrc
