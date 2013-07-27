#-------------------------------------------------
#
# Project created by QtCreator 2010-07-22T22:43:13
#
#-------------------------------------------------
QT += core
QT -= gui
SOURCES += \
    beerwanter.cpp \
    mainWt.cpp \
    beerwanterwtwidget.cpp
HEADERS  += \
    beerwanter.h \
    beerwanterwtwidget.h \
    myassert.h
LIBS += -lwt -lwthttp
#Note: the flag below is a workaround for the following error:
#  http://richelbilderbeek.nl/CppCompileErrorCc1plusInternalCompilerErrorSegmentationFault.htm
#Drawback: all asserts will removed as well
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   += qt
CONFIG   -= app_bundle
TEMPLATE = app
