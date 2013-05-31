QT       += core
QT       -= gui
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

#Turn threads off for quick execution
#Turn threads on for linear debugging
#DEFINES += SADC_USE_THREADS

LIBS += -lboost_system -lboost_filesystem -lboost_program_options -lboost_regex

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppChess \
    ../../Classes/CppTrace

SOURCES += main.cpp \ 
    ../../Classes/CppChess/chesspiece.cpp \
    ../../Classes/CppChess/chessmove.cpp \
    ../../Classes/CppChess/chesscolor.cpp \
    ../../Classes/CppChess/chesssquare.cpp \
    ../../Classes/CppChess/chessboard.cpp \
    ../../Classes/CppChess/chessscore.cpp \
    ../../Classes/CppChess/chessrank.cpp \
    ../../Classes/CppChess/chessplayer.cpp \
    ../../Classes/CppChess/chesspiecetest.cpp \
    ../../Classes/CppChess/chessmovetest.cpp \
    ../../Classes/CppChess/chessmoves.cpp \
    ../../Classes/CppChess/chessgame.cpp \
    ../../Classes/CppChess/chessfile.cpp \
    ../../Classes/CppChess/chesscastling.cpp \
    ../../Classes/CppChess/chessboardtest.cpp \
    ../../Classes/CppChess/chessbitboard.cpp \
    searchanddestroychessmenudialog.cpp \
    searchanddestroychessgamedialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppChess/chessboardfactory.cpp \
    ../../Classes/CppChess/chesshelper.cpp \
    ../../Classes/CppChess/chesspiecefactory.cpp \
    ../../Classes/CppChess/chesssquarefactory.cpp \
    ../../Classes/CppChess/chessmovefactory.cpp

HEADERS += \
    ../../Classes/CppChess/chesspiece.h \
    ../../Classes/CppChess/chessmove.h \
    ../../Classes/CppChess/chesscolor.h \
    ../../Classes/CppChess/chesssquare.h \
    ../../Classes/CppChess/chessboard.h \
    ../../Classes/CppChess/chessscore.h \
    ../../Classes/CppChess/chessrank.h \
    ../../Classes/CppChess/chessplayer.h \
    ../../Classes/CppChess/chessmoves.h \
    ../../Classes/CppChess/chessgame.h \
    ../../Classes/CppChess/chessfwd.h \
    ../../Classes/CppChess/chessfile.h \
    ../../Classes/CppChess/chesscastling.h \
    ../../Classes/CppChess/chessbitboard.h \
    searchanddestroychessmenudialog.h \
    searchanddestroychessgamedialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppChess/chessboardfactory.h \
    ../../Classes/CppChess/chesshelper.h \
    ../../Classes/CppChess/chesspiecefactory.h \
    ../../Classes/CppChess/chesssquarefactory.h \
    ../../Classes/CppChess/chessmovefactory.h

OTHER_FILES += \
    ../../Classes/CppChess/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppWidget/Licence.txt \
    ../../Classes/CppAbout/Licence.txt
