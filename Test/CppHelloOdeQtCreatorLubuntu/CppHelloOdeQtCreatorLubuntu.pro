TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
SOURCES += main.cpp
INCLUDEPATH += ../../Libraries/opende-code/include
INCLUDEPATH += ../../Libraries/opende-code/ode/demo

#The Open Dynamics Engine (ODE)
LIBS += -lode

#The Open Dynamics Engine its drawstuff library
LIBS += -L../../Libraries/opende-code/drawstuff/src -ldrawstuff

#POSIX thread
LIBS += -lpthread

#Open Graphics Library (OpenGL)
LIBS += -lGL

#The X11 display server
LIBS += -lX11

#OpenGL Utilities (GLU)
LIBS += -lGLU
