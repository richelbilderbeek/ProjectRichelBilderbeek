#-------------------------------------------------
#
# Project created by QtCreator 2011-04-10T11:16:42
#
#-------------------------------------------------
QT       -= core
QT       -= gui
LIBS += \
  -lwt -lwthttp \
  -lboost_program_options \
  -lboost_signals \
  -lboost_thread
QMAKE_CXXFLAGS += -DNDEBUG
#QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppTrace \
  ../../Classes/CppWtAboutDialog

SOURCES += wtmain.cpp \
  wtpaperrockscissorsdialog.cpp \
  wtpaperrockscissorsserver.cpp \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
  wtpaperrockscissorsevent.cpp \
    wtpaperrockscissorsdialogstate.cpp
HEADERS += \
  wtpaperrockscissorsdialog.h \
  wtpaperrockscissorsevent.h \
  wtpaperrockscissorsserver.h \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    wtpaperrockscissorsdialogstate.h \
    ../../Classes/CppTrace/trace.h
