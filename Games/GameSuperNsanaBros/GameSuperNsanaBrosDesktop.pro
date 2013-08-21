QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppTrace \
  ../../Classes/CppQtAboutDialog

SOURCES += qtmain.cpp \
  nsanabrosgamearea2dwidget.cpp \
  nsanabrosgamedialog.cpp \
  nsanabroskeys.cpp \
  nsanabroskeyswidget.cpp \
  nsanabrosmenudialog.cpp \
  nsanabrosoptionsdialog.cpp \
  nsanabrosplayer.cpp \
  nsanabrossprite.cpp \
  qtnsanabrosgamearea2dwidget.cpp \
  qtnsanabrosgamedialog.cpp \
  qtnsanabroskeyswidget.cpp \
  qtnsanabrosmenudialog.cpp \
  qtnsanabrosoptionsdialog.cpp \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    nsanabrosoptions.cpp \
    nsanabrosgame.cpp

HEADERS  += \
  nsanabrosgamearea2dwidget.h \
  nsanabrosgamedialog.h \
  nsanabroskeyswidget.h \
  nsanabroskeys.h \
  nsanabrosmenudialog.h \
  nsanabrosoptionsdialog.h \
  nsanabrosqtheader.h \
  nsanabrosplayer.h \
  nsanabrossprite.h \
  nsanabrosstlheader.h \
  qtnsanabrosgamearea2dwidget.h \
  qtnsanabrosgamedialog.h \
  qtnsanabroskeyswidget.h \
  qtnsanabrosmenudialog.h \
  qtnsanabrosoptionsdialog.h \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
  ../../Classes/CppTrace/trace.h \
    nsanabrosoptions.h \
    nsanabrosgame.h \
    nsanabrosstlfwdheader.h

FORMS += \
  qtnsanabrosgamedialog.ui \
  qtnsanabrosmenudialog.ui \
  qtnsanabrosoptionsdialog.ui \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
