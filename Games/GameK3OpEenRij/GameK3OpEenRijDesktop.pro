QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace \
    ../../Games/GameConnectThree

SOURCES += qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.cpp \
    ../GameConnectThree/connectthreefilenames.cpp \
    ../GameConnectThree/qtshowwinnerdialog.cpp \
    ../GameConnectThree/qtselectplayerwidget.cpp \
    ../GameConnectThree/qtconnectthreeresources.cpp \
    ../GameConnectThree/qtconnectthreemenudialog.cpp \
    ../GameConnectThree/qtconnectthreegamedialog.cpp \
    ../GameConnectThree/connectthreeresources.cpp \
    ../GameConnectThree/connectthreemenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.h \
    ../GameConnectThree/connectthreefilenames.h \
    ../../Classes/CppTrace/trace.h \
    ../GameConnectThree/qtshowwinnerdialog.h \
    ../GameConnectThree/qtselectplayerwidget.h \
    ../GameConnectThree/qtconnectthreeresources.h \
    ../GameConnectThree/qtconnectthreemenudialog.h \
    ../GameConnectThree/qtconnectthreegamedialog.h \
    ../GameConnectThree/connectthreeresources.h \
    ../GameConnectThree/connectthreemenudialog.h

OTHER_FILES += \
    K3OpEenRij.css \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../GameConnectThree/zip.sh \
    ../GameConnectThree/R.png \
    ../GameConnectThree/Licence.txt \
    ../GameConnectThree/GameConnectThreeWelcomeNoLegend.png \
    ../GameConnectThree/GameConnectThreeWelcome.png \
    ../GameConnectThree/GameConnectThreeLubuntuToWindows.sh \
    ../GameConnectThree/GameConnectThree.css \
    ../GameConnectThree/ConnectThreeWrong.png \
    ../GameConnectThree/ConnectThreePlayer3Grey.png \
    ../GameConnectThree/ConnectThreePlayer3.png \
    ../GameConnectThree/ConnectThreePlayer2Grey.png \
    ../GameConnectThree/ConnectThreePlayer2.png \
    ../GameConnectThree/ConnectThreePlayer1Grey.png \
    ../GameConnectThree/ConnectThreePlayer1.png \
    ../GameConnectThree/ConnectThreeGood2.png \
    ../GameConnectThree/ConnectThreeGood1.png \
    ../GameConnectThree/ConnectThreeEmpty.png \
    ../GameConnectThree/ConnectThreeComputerGrey.png \
    ../GameConnectThree/ConnectThreeComputer3.png \
    ../GameConnectThree/ConnectThreeComputer2.png \
    ../GameConnectThree/ConnectThreeComputer1.png

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../GameConnectThree/qtshowwinnerdialog.ui \
    ../GameConnectThree/qtconnectthreemenudialog.ui \
    ../GameConnectThree/qtconnectthreegamedialog.ui

RESOURCES += \
    ../GameConnectThree/resources.qrc \
    ../GameConnectThree/resources.qrc \
    ../GameConnectThree/GameConnectThree.qrc
