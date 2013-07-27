
QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

CONFIG   += console
CONFIG   -= app_bundle

LIBS += \
    -lboost_filesystem \
    -lboost_regex \
    -lboost_system

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppChess \
    ../../Classes/CppChessResources \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtChess \
    ../../Classes/CppRectangle \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget


SOURCES += qtmain.cpp \
    ../../Classes/CppChess/chesssquareselector.cpp \
    ../../Classes/CppChess/chesssquare.cpp \
    ../../Classes/CppChessResources/chessresources.cpp \
    ../../Classes/CppChess/chesspiece.cpp \
    ../../Classes/CppChess/chessmove.cpp \
    ../../Classes/CppChess/chesscolor.cpp \
    ../../Classes/CppChess/chesswidget.cpp \
    ../../Classes/CppChess/chessboard.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppChess/chessfile.cpp \
    ../../Classes/CppChess/chessrank.cpp \
    ../../Classes/CppChess/chessscore.cpp \
    ../../Classes/CppChess/chessmoves.cpp \
    ../../Classes/CppChess/chessmovetest.cpp \
    ../../Classes/CppChess/chesspiecetest.cpp \
    ../../Classes/CppChess/chessboardtest.cpp \
    ../../Classes/CppChess/chessbitboard.cpp \
    qttestchessmenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    testchessmenudialog.cpp \
    qttestchessgamedialog.cpp \
    ../../Classes/CppQtChess/qtchessboardwidget.cpp \
    ../../Classes/CppQtChess/qtchessresources.cpp \
    qttestchessviewresourcesdialog.cpp \
    ../../Classes/CppChess/chessgame.cpp \
    ../../Classes/CppChess/chessplayer.cpp \
    qttestchessboarddialog.cpp \
    ../../Classes/CppChess/chessboardwidget.cpp \
    ../../Classes/CppChess/chessgamewidget.cpp \
    ../../Classes/CppChess/chesscastling.cpp

HEADERS += \
    ../../Classes/CppChess/chesssquareselector.h \
    ../../Classes/CppChess/chesssquare.h \
    ../../Classes/CppChessResources/chessresources.h \
    ../../Classes/CppChess/chesspiece.h \
    ../../Classes/CppChess/chessmove.h \
    ../../Classes/CppChess/chessfwd.h \
    ../../Classes/CppChess/chesscolor.h \
    ../../Classes/CppChess/chesswidget.h \
    ../../Classes/CppChess/chessboard.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppChess/chessfile.h \
    ../../Classes/CppChess/chessrank.h \
    ../../Classes/CppChess/chessscore.h \
    ../../Classes/CppChess/chessmoves.h \
    ../../Classes/CppChess/chessboard.h \
    ../../Classes/CppChess/chessbitboard.h \
    qttestchessmenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    testchessmenudialog.h \
    qttestchessgamedialog.h \
    ../../Classes/CppQtChess/qtchessboardwidget.h \
    ../../Classes/CppQtChess/qtchessresources.h \
    ../../Classes/CppQtChess/qtchessresources.h \
    qttestchessviewresourcesdialog.h \
    ../../Classes/CppChess/chessgame.h \
    ../../Classes/CppChess/chessplayer.h \
    ../../Classes/CppChess/chesswidget.h \
    qttestchessboarddialog.h \
    ../../Classes/CppChess/chessboardwidget.h \
    ../../Classes/CppChess/chessgamewidget.h \
    ../../Classes/CppChess/chesscastling.h

FORMS += \
    qttestchessmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestchessgamedialog.ui \
    qttestchessviewresourcesdialog.ui \
    qttestchessboarddialog.ui

RESOURCES += \
    ../../Classes/CppChessResources/chessresources.qrc
