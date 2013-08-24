TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x
SOURCES += main.cpp
DEFINES += NDEBUG
LIBS += -lboost_program_options
