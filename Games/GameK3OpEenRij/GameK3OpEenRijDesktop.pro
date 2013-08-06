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
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace \
    ../../Games/GameConnectThree

SOURCES += qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../GameConnectThree/connectthreeresources.cpp \
    ../GameConnectThree/qtconnectthreegamedialog.cpp \
    ../GameConnectThree/qtshowwinnerdialog.cpp \
    k3opeenrijmenudialog.cpp \
    qtk3opeenrijinstructionsdialog.cpp \
    qtk3opeenrijmenudialog.cpp \
    qtk3opeenrijselectplayerwidget.cpp \
    qtk3opeenrijresources.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    ../GameConnectThree/connectthreeresources.h \
    ../GameConnectThree/qtconnectthreegamedialog.h \
    ../GameConnectThree/qtshowwinnerdialog.h \
    k3opeenrijmenudialog.h \
    qtk3opeenrijinstructionsdialog.h \
    qtk3opeenrijmenudialog.h \
    qtk3opeenrijselectplayerwidget.h \
    qtk3opeenrijresources.h

OTHER_FILES += \
    ../../Classes/CppConnectThreeWidget/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
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
    K3OpEenRij.css

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../GameConnectThree/qtconnectthreegamedialog.ui \
    ../GameConnectThree/qtshowwinnerdialog.ui \
    qtk3opeenrijinstructionsdialog.ui \
    qtk3opeenrijmenudialog.ui

RESOURCES += \
    GameK3OpEenRij.qrc

