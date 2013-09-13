QT       -= core gui
TARGET = CppStaticLibraryQtCreatorExample1
TEMPLATE = lib
CONFIG += staticlib
SOURCES += cppstaticlibraryqtcreatorexample1.cpp
HEADERS += cppstaticlibraryqtcreatorexample1.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
