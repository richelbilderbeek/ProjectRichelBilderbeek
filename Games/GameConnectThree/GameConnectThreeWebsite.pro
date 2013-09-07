QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_filesystem -lboost_signals -lboost_system -lboost_program_options
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

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.cpp \
    connectthreemenudialog.cpp \
    connectthreeresources.cpp \
    wtconnectthreegamedialog.cpp \
    wtconnectthreemenudialog.cpp \
    wtconnectthreeresources.cpp \
    wtmain.cpp \
    wtselectplayerwidget.cpp \
    qtconnectthreeresources.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.h \
    connectthreemenudialog.h \
    connectthreeresources.h \
    wtconnectthreegamedialog.h \
    wtconnectthreemenudialog.h \
    wtconnectthreeresources.h \
    wtselectplayerwidget.h \
    qtconnectthreeresources.h

RESOURCES += \
    GameConnectThree.qrc
