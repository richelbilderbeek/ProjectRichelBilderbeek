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
  ../../Classes/CppShinyButton \
  ../../Classes/CppShinyButtonWidget \
  ../../Classes/CppTrace \
  ../../Classes/CppWidget \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtDialWidget \
  ../../Classes/CppWtShinyButtonWidget

SOURCES +=\
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppShinyButton/shinybutton.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
  ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppRainbow/rainbow.cpp \
    main.cpp

HEADERS  += \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppShinyButton/shinybutton.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppRainbow/rainbow.h
