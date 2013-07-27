QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_signals -lboost_regex -lboost_system -lboost_filesystem -lboost_program_options
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppIpAddress \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtEntrance

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    testentrancemenudialog.cpp \
    ../../Classes/CppWtEntrance/wtentrance.cpp \
    ../../Classes/CppIpAddress/ipaddress.cpp \
    wttestentrancemenudialog.cpp \
    wttestentrancemaindialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    testentrancemenudialog.h \
    ../../Classes/CppWtEntrance/wtentrance.h \
    ../../Classes/CppIpAddress/ipaddress.h \
    wttestentrancemenudialog.h \
    wttestentrancemaindialog.h

RESOURCES += \
    ToolTestEntrance.qrc
