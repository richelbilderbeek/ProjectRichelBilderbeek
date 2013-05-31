QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout

SOURCES += main.cpp \
    pausemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp

HEADERS += \
    pausemenudialog.h \
    ../../Classes/CppAbout/about.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt
