QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include( ToolAsciiArter.pri )

INCLUDEPATH += \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig

SOURCES += \
  wtmain.cpp \
  wtasciiartermaindialog.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
  ../../Classes/CppWtAutoConfig/wtautoconfig.cpp

HEADERS  += \
  wtasciiartermaindialog.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  ../../Classes/CppWtAutoConfig/wtautoconfig.h

RESOURCES += \
    ToolAsciiArter.qrc

#
#
# Boost
#
#

LIBS += \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_signals \
  -lboost_system


#
#
# Wt
#
#

LIBS += -lwt -lwthttp
