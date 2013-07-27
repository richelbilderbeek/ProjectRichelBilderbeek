QT       += core
QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

CONFIG   += console
CONFIG   -= app_bundle

LIBS += \
    -lboost_regex \
    -lboost_system

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppChess \
    ../../Classes/CppRectangle \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget


SOURCES += main.cpp \
    ../../Classes/CppChess/chesssquareselector.cpp \
    ../../Classes/CppChess/chesssquare.cpp \
    ../../Classes/CppChess/chessresources.cpp \
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
    ../../Classes/CppChess/chessboard1d.cpp \
    ../../Classes/CppChess/chessboard1dtest.cpp \
    ../../Classes/CppChess/chessbitboard.cpp

HEADERS += \
    ../../Classes/CppChess/chesssquareselector.h \
    ../../Classes/CppChess/chesssquare.h \
    ../../Classes/CppChess/chessresources.h \
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
    ../../Classes/CppChess/chessboard1d.h \
    ../../Classes/CppChess/chessbitboard.h
