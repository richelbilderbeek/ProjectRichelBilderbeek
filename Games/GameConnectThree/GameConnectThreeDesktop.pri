include(../../Games/GameConnectThree/GameConnectThreeConsole.pri)

SOURCES += \
    ../../Games/GameConnectThree/qtshowwinnerdialog.cpp \
    ../../Games/GameConnectThree/qtselectplayerwidget.cpp \
    ../../Games/GameConnectThree/qtconnectthreeresources.cpp \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.cpp \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.cpp \
    ../../Games/GameConnectThree/qtconnectthreecanvas.cpp

HEADERS  += \
    ../../Games/GameConnectThree/qtshowwinnerdialog.h \
    ../../Games/GameConnectThree/qtselectplayerwidget.h \
    ../../Games/GameConnectThree/qtconnectthreeresources.h \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.h \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.h \
    ../../Games/GameConnectThree/qtconnectthreecanvas.h

FORMS += \
    ../../Games/GameConnectThree/qtshowwinnerdialog.ui \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.ui \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.ui

# Moved to GameConnectThreeConsole.pri
# RESOURCES += \
#     ../../Games/GameConnectThree/GameConnectThree.qrc

