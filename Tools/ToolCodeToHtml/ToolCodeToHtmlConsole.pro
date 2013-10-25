QT += core
QT -= gui
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    main.cpp

include( ToolCodeToHtml.pri )
