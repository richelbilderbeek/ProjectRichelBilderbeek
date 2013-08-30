greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtShapeWidget \
    ../../Classes/CppRectangle \
    ../../Classes/CppShape \
    ../../Classes/CppShapeWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget

SOURCES += qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppShapeWidget/shapewidget.cpp \
    ../../Classes/CppShape/shape.cpp \
    ../../Classes/CppQtShapeWidget/qtshapewidget.cpp \
    qttestshapemaindialog.cpp \
    qttestshapemenudialog.cpp \
    testshapemaindialog.cpp \
    testshapemenudialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppShapeWidget/shapewidget.h \
    ../../Classes/CppShape/shape.h \
    ../../Classes/CppQtShapeWidget/qtshapewidget.h \
    ../../Classes/CppTrace/trace.h \
    qttestshapemaindialog.h \
    qttestshapemenudialog.h \
    testshapemaindialog.h \
    testshapemenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestshapemaindialog.ui \
    qttestshapemenudialog.ui

RESOURCES += \
    ToolTestShape.qrc
