#-------------------------------------------------
#
# Project created by QtCreator 2011-01-10T18:25:31
#
#-------------------------------------------------
QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_filesystem
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += mainwt.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.cpp \
    ../../Games/GameConnectThree/wtconnectthreedialog.cpp \
    ../../Games/GameConnectThree/wtconnectthreemenudialog.cpp \
    ../../Games/GameConnectThree/wtconnectthreegamedialog.cpp \
    ../../Games/GameConnectThree/wtselectplayerwidget.cpp \
    ../GameConnectThree/connectthreefilenames.cpp
HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.h \
    ../../Games/GameConnectThree/wtconnectthreedialog.h \
    ../../Games/GameConnectThree/wtconnectthreemenudialog.h \
    ../../Games/GameConnectThree/wtconnectthreegamedialog.h \
    ../../Games/GameConnectThree/wtselectplayerwidget.h \
    ../GameConnectThree/connectthreefilenames.h

OTHER_FILES += \
    K3OpEenRij.css
