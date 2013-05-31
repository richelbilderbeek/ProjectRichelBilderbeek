QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_filesystem
QMAKE_CXXFLAGS += -std=c++11
#  -DNDEBUG \

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtConnectThreeWidget

SOURCES += wtmain.cpp \
    wtconnectthreemenudialog.cpp \
    wtconnectthreegamedialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    wtselectplayerwidget.cpp \
    connectthreeresources.cpp \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    connectthreemenudialog.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp \
    wtconnectthreeresources.cpp
HEADERS += \
    wtconnectthreemenudialog.h \
    wtconnectthreegamedialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    wtselectplayerwidget.h \
    connectthreeresources.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    connectthreemenudialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    wtconnectthreeresources.h

RESOURCES += \
    GameConnectThree.qrc
