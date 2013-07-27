#This application uses QImage for image conversion
QT       += core gui
LIBS += -lwt -lwthttp -lboost_program_options
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppAsciiArter \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig

SOURCES += \
  asciiartermaindialog.cpp \
  wtmain.cpp \
  wtasciiartermaindialog.cpp \
  ../../Classes/CppAsciiArter/asciiarter.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp

HEADERS  += \
  asciiartermaindialog.h \
  wtasciiartermaindialog.h \
  ../../Classes/CppAsciiArter/asciiarter.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h

RESOURCES += \
    ToolAsciiArter.qrc
