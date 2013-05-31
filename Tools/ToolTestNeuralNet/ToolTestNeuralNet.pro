#-------------------------------------------------
#
# Project created by QtCreator 2010-09-17T11:20:38
#
#-------------------------------------------------

QT       += core gui


CONFIG(debug, debug|release) {
  TARGET = TestNeuralNetDebug
  message(Building debug version)

} else {
  TARGET = TestNeuralNetRelease
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
    resources.qrc
