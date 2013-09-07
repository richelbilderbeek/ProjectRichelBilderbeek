QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_filesystem
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppChess \
    ../../Classes/CppRectangle \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtServerPusher \
    ../../Classes/CppWtChessBoardWidget \
    ../../Classes/CppWtTimedServerPusher

HEADERS += \
    ../../Classes/CppChess/chessboard.h \
    ../../Classes/CppChess/chessmove.h \
    ../../Classes/CppChess/chesspiece.h \
    ../../Classes/CppChess/chesssquare.h \
    ../../Classes/CppChess/chesssquareselector.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWtChessBoardWidget/wtchessboardwidget.h \
    searchanddestroychessqtmenudialog.h \
    searchanddestroychessqtgamedialog.h \
    searchanddestroychessmenudialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppChess/chessfwd.h \
    ../../Classes/CppChess/chessresources.h \
    ../../Classes/CppWtChessBoardWidget/wtchessresources.h \
    ../../Classes/CppChess/chessboardwidget.h \
    ../../Classes/CppChess/chessboard2d.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppChess/chesssquarefactory.h
SOURCES += wtmain.cpp \
    ../../Classes/CppChess/chessboard.cpp \
    ../../Classes/CppChess/chessmove.cpp \
    ../../Classes/CppChess/chesspiece.cpp \
    ../../Classes/CppChess/chesssquare.cpp \
    ../../Classes/CppChess/chesssquareselector.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtChessBoardWidget/wtchessboardwidget.cpp \
    searchanddestroychessmenudialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppChess/chessresources.cpp \
    ../../Classes/CppWtChessBoardWidget/wtchessresources.cpp \
    ../../Classes/CppChess/chessboardwidget.cpp \
    ../../Classes/CppChess/chessboard2d.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppChess/chesssquarefactory.cpp

OTHER_FILES += \
    GameSearchAndDestroyChessArchitecture.txt
