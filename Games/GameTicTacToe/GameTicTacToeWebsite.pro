
QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppTicTacToe \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtTicTacToeWidget

SOURCES += \
    tictactoemenudialog.cpp \
    wtmain.cpp \
    wttictactoegamedialog.cpp \
    wttictactoemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppTicTacToe/tictactoe.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.cpp

HEADERS += \
    tictactoemenudialog.h \
    wttictactoegamedialog.h \
    wttictactoemenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTicTacToe/tictactoe.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.h

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}

#
#
# Wt
#
#

unix {
  LIBS += -lwt -lwthttp
}
