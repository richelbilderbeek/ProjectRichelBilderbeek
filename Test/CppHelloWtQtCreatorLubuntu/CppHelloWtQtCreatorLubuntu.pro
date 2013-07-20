QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_signals

#Needed for older Wt versions
#QMAKE_CXXFLAGS += -DNDEBUG

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
