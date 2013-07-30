QT       += core gui xml
CONFIG(debug, debug|release) {
  message(Building debug version)

} else {
  DEFINES += NDEBUG
  message(Building release version)
}
TEMPLATE = app
SOURCES += main.cpp\
        dialogmain.cpp \
    ../ToolTestTicTacToe/tictactoe.cpp \
    dialogabout.cpp \
    dialogwhatsnew.cpp \
    statevaluegraph.cpp \
    statevaluevertex.cpp \
    statevalueedge.cpp
HEADERS  += \
    dialogmain.h \
    ../ToolTestTicTacToe/tictactoe.h \
    dialogabout.h \
    dialogwhatsnew.h \
    statevaluegraph.h \
    statevaluevertex.h \
    statevalueedge.h
FORMS    += dialogmain.ui \
    dialogabout.ui \
    ../ToolTestTicTacToe/dialogwhatsnew.ui \
    dialogwhatsnew.ui
RESOURCES += \
    ToolTicTacToeValuer.qrc
#Disable depreciated warning, caused by boost/graph/adjacency_list.hpp
#  including the depreciated hash_set
QMAKE_CXXFLAGS_DEBUG   += -Wno-deprecated
QMAKE_CXXFLAGS_RELEASE += -Wno-deprecated
