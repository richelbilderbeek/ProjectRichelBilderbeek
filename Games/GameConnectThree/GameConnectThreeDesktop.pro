#-------------------------------------------------
#
# Project created by QtCreator 2010-12-29T12:28:36
#
#-------------------------------------------------
QT       += core gui
TARGET = GameConnectThreeDesktop
TEMPLATE = app
LIBS += -lboost_system -lboost_filesystem
QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtConnectThreeWidget \
    ../../Classes/CppTrace

SOURCES += qtmain.cpp \
    qtconnectthreegamedialog.cpp \
    qtconnectthreemenudialog.cpp \
    qtselectplayerwidget.cpp \
    qtshowwinnerdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.cpp \
    connectthreeresources.cpp \
    connectthreemenudialog.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp \
    qtconnectthreeresources.cpp
HEADERS  += \
    qtconnectthreegamedialog.h \
    qtconnectthreemenudialog.h \
    qtselectplayerwidget.h \
    qtshowwinnerdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAssert/assert.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.h \
    connectthreeresources.h \
    ../../Classes/CppTrace/trace.h \
    connectthreemenudialog.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    qtconnectthreeresources.h
FORMS    += \
    qtconnectthreemenudialog.ui \
    qtconnectthreegamedialog.ui \
    qtshowwinnerdialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    GameConnectThree.qrc
