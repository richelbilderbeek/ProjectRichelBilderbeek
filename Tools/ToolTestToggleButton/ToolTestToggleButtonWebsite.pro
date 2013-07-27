#-------------------------------------------------
#
# Project created by QtCreator 2011-04-11T09:14:30
#
#-------------------------------------------------
QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppDial \
  ../../Classes/CppDialWidget \
  ../../Classes/CppRainbow \
  ../../Classes/CppRectangle \
  ../../Classes/CppToggleButton \
  ../../Classes/CppToggleButtonWidget \
  ../../Classes/CppTrace \
  ../../Classes/CppWidget \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtDialWidget \
  ../../Classes/CppWtToggleButtonWidget

SOURCES += wtmain.cpp\
  testtogglebuttonmenudialog.cpp \
  wttesttogglebuttonmaindialog.cpp \
  wttesttogglebuttonmenudialog.cpp \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppToggleButton/togglebutton.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
  ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppRainbow/rainbow.cpp

HEADERS  += \
  testtogglebuttonmenudialog.h \
  wttesttogglebuttonmaindialog.h \
  wttesttogglebuttonmenudialog.h \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppToggleButton/togglebutton.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppRainbow/rainbow.h

RESOURCES += \
    ToolTestToggleButton.qrc
