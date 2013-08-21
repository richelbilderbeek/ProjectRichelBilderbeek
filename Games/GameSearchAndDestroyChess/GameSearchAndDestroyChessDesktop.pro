QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

CONFIG   -= console
CONFIG   -= app_bundle
TEMPLATE = app

LIBS += -lboost_regex -lboost_system -lboost_filesystem

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppChess \
    ../../Classes/CppChessResources \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtChess \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppRectangle \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget

SOURCES += qtmain.cpp \ 
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppChess/chessbitboard.cpp \
    ../../Classes/CppChess/chessboard.cpp \
    ../../Classes/CppChess/chessboardtest.cpp \
    ../../Classes/CppChess/chessboardwidget.cpp \
    ../../Classes/CppChess/chesscastling.cpp \
    ../../Classes/CppChess/chesscolor.cpp \
    ../../Classes/CppChess/chessfile.cpp \
    ../../Classes/CppChess/chessgame.cpp \
    ../../Classes/CppChess/chessgamewidget.cpp \
    ../../Classes/CppChess/chessmove.cpp \
    ../../Classes/CppChess/chessmoves.cpp \
    ../../Classes/CppChess/chessmovetest.cpp \
    ../../Classes/CppChess/chesspiece.cpp \
    ../../Classes/CppChess/chesspiecetest.cpp \
    ../../Classes/CppChess/chessplayer.cpp \
    ../../Classes/CppChess/chessrank.cpp \
    ../../Classes/CppChess/chessscore.cpp \
    ../../Classes/CppChess/chesssquare.cpp \
    ../../Classes/CppChess/chesssquareselector.cpp \
    ../../Classes/CppChess/chesswidget.cpp \
    ../../Classes/CppChessResources/chessresources.cpp \
    ../../Classes/CppQtChess/qtchessboardwidget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWidget/widget.cpp \
    qtsearchanddestroychessgamedialog.cpp \
    qtsearchanddestroychessmenudialog.cpp \
    searchanddestroychessmenudialog.cpp \
    ../../Classes/CppQtChess/qtchessresources.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppChess/chesssquarefactory.cpp \
    ../../Classes/CppChess/chessmovefactory.cpp \
    ../../Classes/CppChess/chesspiecefactory.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppChess/chessbitboard.h \
    ../../Classes/CppChess/chessboard.h \
    ../../Classes/CppChess/chessboardwidget.h \
    ../../Classes/CppChess/chesscastling.h \
    ../../Classes/CppChess/chesscolor.h \
    ../../Classes/CppChess/chessfile.h \
    ../../Classes/CppChess/chessfwd.h \
    ../../Classes/CppChess/chessgame.h \
    ../../Classes/CppChess/chessgamewidget.h \
    ../../Classes/CppChess/chessmove.h \
    ../../Classes/CppChess/chessmoves.h \
    ../../Classes/CppChess/chesspiece.h \
    ../../Classes/CppChess/chessplayer.h \
    ../../Classes/CppChess/chessrank.h \
    ../../Classes/CppChess/chessscore.h \
    ../../Classes/CppChess/chesssquare.h \
    ../../Classes/CppChess/chesssquareselector.h \
    ../../Classes/CppChess/chesswidget.h \
    ../../Classes/CppChessResources/chessresources.h \
    ../../Classes/CppQtChess/qtchessboardwidget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWidget/widget.h \
    qtsearchanddestroychessgamedialog.h \
    qtsearchanddestroychessmenudialog.h \
    searchanddestroychessmenudialog.h \
    searchanddestroychessresources.h \
    ../../Classes/CppQtChess/qtchessresources.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppChess/chesssquarefactory.h \
    ../../Classes/CppChess/chessmovefactory.h \
    ../../Classes/CppChess/chesspiecefactory.h

FORMS += \
    qtsearchanddestroychessgamedialog.ui \
    qtsearchanddestroychessmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ../../Classes/CppChessResources/chessresources.qrc

OTHER_FILES += \
    ../../Classes/CppChessResources/Licence.txt \
    ../../Classes/CppChess/Licence.txt \
    ../../Classes/CppQtChess/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt
