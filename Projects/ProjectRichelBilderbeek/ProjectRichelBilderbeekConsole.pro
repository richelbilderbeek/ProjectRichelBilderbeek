# Go ahead and use Qt.Core: it is about as platform-independent as
# the STL and Boost
QT += core

# Don't define gui: it would defy the purpose of this console
# application to work non-GUI
QT -= gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include( ProjectRichelBilderbeek.pri )

SOURCES += main.cpp
