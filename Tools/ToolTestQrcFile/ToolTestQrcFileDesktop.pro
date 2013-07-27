QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppAbout/about.cpp \
    testqrcfilemenudialog.cpp \
    qttestqrcfilemenudialog.cpp \
    qttestqrcfilemaindialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp

HEADERS += \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h \
    testqrcfilemenudialog.h \
    qttestqrcfilemenudialog.h \
    qttestqrcfilemaindialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h

FORMS += \
    qttestqrcfilemenudialog.ui \
    qttestqrcfilemaindialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolTestQrcFile.qrc
