QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtTicTacToeWidget \
    ../../Classes/CppTicTacToe \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtTicTacToeWidget/qttictactoewidget.cpp \
    ../../Classes/CppTicTacToe/tictactoe.cpp \
    qtmain.cpp \
    qttooltesttictactoemaindialog.cpp \
    qttooltesttictactoemenudialog.cpp \
    tooltesttictactoemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp

HEADERS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtTicTacToeWidget/qttictactoewidget.h \
    ../../Classes/CppTicTacToe/tictactoe.h \
    qttooltesttictactoemaindialog.h \
    qttooltesttictactoemenudialog.h \
    tooltesttictactoemenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h

FORMS += \
    qttooltesttictactoemaindialog.ui \
    qttooltesttictactoemenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ToolTestTicTacToe.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppTicTacToe/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtTicTacToeWidget/Licence.txt \
    ../../Classes/CppTrace/Licence.txt

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
