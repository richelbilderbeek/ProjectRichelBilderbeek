QT       -= core
QT       -= gui
LIBS += \
  -lwt -lwthttp \
  -lboost_program_options \
  -lboost_signals \
  -lboost_thread
  
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppTrace \
  ../../Classes/CppWtAboutDialog

SOURCES += \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
  wtmain.cpp \
  wtpaperrockscissorsdialog.cpp \
  wtpaperrockscissorsdialogstate.cpp \
  wtpaperrockscissorsevent.cpp \
  wtpaperrockscissorsserver.cpp

HEADERS += \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppTrace/trace.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  wtpaperrockscissorsdialog.h \
  wtpaperrockscissorsdialogstate.h \
  wtpaperrockscissorsevent.h \
  wtpaperrockscissorsserver.h
