#-------------------------------------------------
#
# Project created by QtCreator 2011-03-28T16:12:00
#
#-------------------------------------------------
QT += core
QT -= gui     
LIBS += -lwt -lwthttp -lboost_program_options
QMAKE_CXXFLAGS += \
  -DNDEBUG \
  -std=c++0x

TARGET = GameSuperNsanaBrosWebsite
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppTrace \
  ../../Classes/CppWtAboutDialog

SOURCES += wtmain.cpp \
  nsanabrosgamearea2d.cpp \
  nsanabrosgamearea2dwidget.cpp \
  nsanabrosgamedialog.cpp \
  nsanabroskeys.cpp \
  nsanabroskeyswidget.cpp \
  nsanabrosmenudialog.cpp \
  nsanabrosoptionsdialog.cpp \
  nsanabrosplayer.cpp \
  nsanabrossprite.cpp \
  wtnsanabrosgameareawidget.cpp \
  wtnsanabrosgamedialog.cpp \
  wtnsanabroskeyswidget.cpp \
  wtnsanabrosmenudialog.cpp \
  wtnsanabrosoptionsdialog.cpp \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp

HEADERS  += \
  nsanabrosgamearea2d.h \
  nsanabrosgamearea2dwidget.h \
  nsanabrosgamedialog.h \
  nsanabroskeys.h \
  nsanabroskeyswidget.h \
  nsanabrosmenudialog.h \
  nsanabrosoptionsdialog.h \
  nsanabrosplayer.h \
  nsanabrossprite.h \
  wtnsanabrosgameareawidget.h \
  wtnsanabrosgameareawidget.h \
  wtnsanabrosgamedialog.h \
  wtnsanabroskeyswidget.h \
  wtnsanabrosmenudialog.h \
  wtnsanabrosmenudialog.h \
  wtnsanabrosoptionsdialog.h \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppTrace/trace.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    nsanabroswtheader.h \
    nsanabrosstlheader.h
