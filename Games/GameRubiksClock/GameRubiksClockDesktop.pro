QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppRectangle \
    ../../Classes/CppRubiksClock \
    ../../Classes/CppRubiksClockWidget \
    ../../Classes/CppToggleButton \
    ../../Classes/CppToggleButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtDialWidget \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtRubiksClockWidget \
    ../../Classes/CppQtToggleButtonWidget

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtDialWidget/qtdialwidget.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.cpp \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppRubiksClock/rubiksclock.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    qtrubiksclockmaindialog.cpp \
    qtrubiksclockmenudialog.cpp \
    rubiksclockmenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtDialWidget/qtdialwidget.h \
    ../../Classes/CppQtDialWidget/qtdialwidget.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.h \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppRubiksClock/rubiksclock.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWidget/widget.h \
    qtrubiksclockmaindialog.h \
    qtrubiksclockmenudialog.h \
    rubiksclockmenudialog.h

RESOURCES += \
    GameRubiksClock.qrc

OTHER_FILES += \
    GameRubiksClockWelcome.png \
    ../../Classes/CppQtDialWidget/Licence.txt \
    ../../Classes/CppQtToggleButtonWidget/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt

FORMS += \
    qtrubiksclockmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtrubiksclockmaindialog.ui
