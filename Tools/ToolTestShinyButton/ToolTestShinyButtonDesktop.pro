QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

#LIBS += -lboost_program_options

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app


INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtShinyButtonWidget \
    ../../Classes/CppRainbow \
    ../../Classes/CppRectangle \
    ../../Classes/CppShinyButton \
    ../../Classes/CppShinyButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppWidget

SOURCES += qtmain.cpp\
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppShinyButton/shinybutton.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtShinyButtonWidget/qtshinybuttonwidget.cpp \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppRainbow/rainbow.cpp \
    testshinybuttonmenudialog.cpp \
    qttestshinybuttonmaindialog.cpp \
    qttestshinybuttonmenudialog.cpp

HEADERS  += \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppShinyButton/shinybutton.h \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
  ../../Classes/CppQtShinyButtonWidget/qtshinybuttonwidget.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppRainbow/rainbow.h \
    testshinybuttonmenudialog.h \
    qttestshinybuttonmaindialog.h \
    qttestshinybuttonmenudialog.h

RESOURCES += \
    ToolTestShinyButton.qrc

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestshinybuttonmenudialog.ui \
    qttestshinybuttonmaindialog.ui
