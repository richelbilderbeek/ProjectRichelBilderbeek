QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

# /myfolder/main.cpp:20: error: undefined reference to `boost::signals::connection::~connection()'
LIBS += -lboost_signals
