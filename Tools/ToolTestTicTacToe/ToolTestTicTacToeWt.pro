QT       += core
QT       -= gui
LIBS += -L/usr/lib -lwt  -lwthttp
#-lwtext
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES +=  \  
    wtmain.cpp \
    ../../Classes/CppTicTacToe/tictactoe.cpp \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.cpp
HEADERS  +=  \
    ../../Classes/CppTicTacToe/tictactoe.h \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.h
