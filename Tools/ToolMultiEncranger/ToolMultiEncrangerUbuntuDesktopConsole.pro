QT -= core gui
LIBS += \
  -lboost_program_options \
  -lboost_system \
  -lboost_filesystem
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += mainUbuntuDesktopConsole.cpp \
    ../../Classes/CppEncranger/encranger.cpp
HEADERS += \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppLoopReader/loopreader.h
