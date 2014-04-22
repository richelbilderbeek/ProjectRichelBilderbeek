include(ToolQmakeWatcherConsole.pri)

INCLUDEPATH += \
    ../../Tools/ToolQmakeWatcher

SOURCES += \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermaindialog.cpp \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermenudialog.cpp

HEADERS += \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermaindialog.h \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermenudialog.h

FORMS    += \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermaindialog.ui \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermenudialog.ui
