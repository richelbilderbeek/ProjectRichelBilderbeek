LIBS += -lwt -lwthttp -lboost_filesystem
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.cpp \
    ../../Games/GameConnectThree/qtconnectthreedialog.cpp \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.cpp \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.cpp \
    ../../Games/GameConnectThree/qtselectplayerwidget.cpp \
    ../GameConnectThree/connectthreefilenames.cpp
HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.h \
    ../../Games/GameConnectThree/qtconnectthreedialog.h \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.h \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.h \
    ../../Games/GameConnectThree/qtselectplayerwidget.h \
    ../GameConnectThree/connectthreefilenames.h

OTHER_FILES += \
    K3OpEenRij.css
