QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

CONFIG   += console
CONFIG   -= app_bundle

LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_signals \
    -lboost_system \
    -lwt \
    -lwthttp

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppChess \
    ../../Classes/CppChessResources \
    ../../Classes/CppRectangle \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtChess


SOURCES += wtmain.cpp \
    ../../Classes/CppChess/chesssquareselector.cpp \
    ../../Classes/CppChess/chesssquare.cpp \
    ../../Classes/CppChessResources/chessresources.cpp \
    ../../Classes/CppChess/chesspiece.cpp \
    ../../Classes/CppChess/chessmove.cpp \
    ../../Classes/CppChess/chesscolor.cpp \
    ../../Classes/CppChess/chessboardwidget.cpp \
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
    wttestchessmenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    testchessmenudialog.cpp \
    wttestchessmaindialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtChess/wtchessresources.cpp \
    ../../Classes/CppWtChess/wtchessboardwidget.cpp

HEADERS += \
    ../../Classes/CppChess/chesssquareselector.h \
    ../../Classes/CppChess/chesssquare.h \
    ../../Classes/CppChessResources/chessresources.h \
    ../../Classes/CppChess/chesspiece.h \
    ../../Classes/CppChess/chessmove.h \
    ../../Classes/CppChess/chessfwd.h \
    ../../Classes/CppChess/chesscolor.h \
    ../../Classes/CppChess/chessboardwidget.h \
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
    wttestchessmenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    testchessmenudialog.h \
    wttestchessmaindialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtChess/wtchessresources.h \
    ../../Classes/CppWtChess/wtchessboardwidget.h

RESOURCES += \
    ../../Classes/CppChessResources/chessresources.qrc \
    ToolTestChess.qrc \
    ../../Classes/CppChessResources/chessresources.qrc
