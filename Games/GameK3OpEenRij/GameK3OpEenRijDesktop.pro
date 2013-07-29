QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app


QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

unix {
  QMAKE_CXXFLAGS += -Werror
}

win32 {
  LIBS += -L../../Libraries/mxe/usr/i686-pc-mingw32/lib
}

LIBS += -lboost_system -lboost_filesystem


INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtConnectThreeWidget \
    ../../Classes/CppTrace \
    ../../Games/GameConnectThree

SOURCES += qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.cpp \
    ../GameConnectThree/connectthreemenudialog.cpp \
    ../GameConnectThree/connectthreeresources.cpp \
    ../GameConnectThree/qtconnectthreegamedialog.cpp \
    ../GameConnectThree/qtconnectthreemenudialog.cpp \
    ../GameConnectThree/qtconnectthreeresources.cpp \
    ../GameConnectThree/qtselectplayerwidget.cpp \
    ../GameConnectThree/qtshowwinnerdialog.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.h \
    ../../Classes/CppTrace/trace.h \
    ../GameConnectThree/connectthreemenudialog.h \
    ../GameConnectThree/connectthreeresources.h \
    ../GameConnectThree/qtconnectthreegamedialog.h \
    ../GameConnectThree/qtconnectthreemenudialog.h \
    ../GameConnectThree/qtconnectthreeresources.h \
    ../GameConnectThree/qtselectplayerwidget.h \
    ../GameConnectThree/qtshowwinnerdialog.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h

OTHER_FILES += \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../GameConnectThree/ConnectThreeComputer1.png \
    ../GameConnectThree/ConnectThreeComputer2.png \
    ../GameConnectThree/ConnectThreeComputer3.png \
    ../GameConnectThree/ConnectThreeComputerGrey.png \
    ../GameConnectThree/ConnectThreeEmpty.png \
    ../GameConnectThree/ConnectThreeGood1.png \
    ../GameConnectThree/ConnectThreeGood2.png \
    ../GameConnectThree/ConnectThreePlayer1Grey.png \
    ../GameConnectThree/ConnectThreePlayer1.png \
    ../GameConnectThree/ConnectThreePlayer2Grey.png \
    ../GameConnectThree/ConnectThreePlayer2.png \
    ../GameConnectThree/ConnectThreePlayer3Grey.png \
    ../GameConnectThree/ConnectThreePlayer3.png \
    ../GameConnectThree/ConnectThreeWrong.png \
    ../GameConnectThree/GameConnectThree.css \
    ../GameConnectThree/GameConnectThreeLubuntuToWindows.sh \
    ../GameConnectThree/GameConnectThreeWelcomeNoLegend.png \
    ../GameConnectThree/GameConnectThreeWelcome.png \
    ../GameConnectThree/Licence.txt \
    ../GameConnectThree/R.png \
    ../GameConnectThree/zip.sh \
    K3OpEenRij.css \
    ../../Classes/CppConnectThreeWidget/Licence.txt

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../GameConnectThree/qtconnectthreegamedialog.ui \
    ../GameConnectThree/qtconnectthreemenudialog.ui \
    ../GameConnectThree/qtshowwinnerdialog.ui

RESOURCES += \
    ../GameConnectThree/GameConnectThree.qrc

