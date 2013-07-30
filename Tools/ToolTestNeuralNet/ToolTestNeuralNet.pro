QT       += core gui

CONFIG(debug, debug|release) {
  message(Building debug version)

} else {
  DEFINES += NDEBUG
  message(Building release version)
}
TEMPLATE = app
LIBS += -L/usr/local/lib -lshark

SOURCES += main.cpp\
        dialogmain.cpp \
    neuralnet.cpp \
    dialogabout.cpp

HEADERS  += dialogmain.h \
    neuralnet.h \
    dialogabout.h

FORMS    += dialogmain.ui \
    dialogabout.ui

RESOURCES += \
    ToolTestNeuralNet.qrc
