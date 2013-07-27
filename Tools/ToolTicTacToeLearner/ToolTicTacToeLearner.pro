#-------------------------------------------------
#
# Project created by QtCreator 2010-08-15T23:08:25
#
#-------------------------------------------------
QT       += core gui

CONFIG(debug, debug|release) {
  message(Building debug version)

} else {
  DEFINES += NDEBUG
  message(Building release version)
}
CONFIG   += console
CONFIG   -= app_bundle
LIBS += -L/usr/local/lib -lshark
LIBS += -L/usr/local/lib -lqwt-qt4
LIBS += -L/usr/local/lib -lQtSvg
TEMPLATE = app
SOURCES += main.cpp \
    ../ToolTestNeuralNet/neuralnet.cpp \
    dialog.cpp \
    dialogabout.cpp \
    ../ToolTestTicTacToe/tictactoe.cpp \
    dialogwhatsnew.cpp
HEADERS += \
    ../ToolTestNeuralNet/neuralnet.h \
    dialog.h \
    dialogabout.h \
    ../ToolTestTicTacToe/tictactoe.h \
    dialogwhatsnew.h
FORMS += \
    dialog.ui \
    dialogabout.ui \
    dialogwhatsnew.ui
RESOURCES += \
    resources.qrc

 release {
   DEFINES += \
      NDEBUG \
      NO_DEBUG
}
