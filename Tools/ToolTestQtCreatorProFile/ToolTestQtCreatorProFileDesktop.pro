QT       += core gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    qtmain.cpp \
    qttestqtcreatorprofilemaindialog.cpp \
    qttestqtcreatorprofilemenudialog.cpp \
    testqtcreatorprofilemenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppTrace/trace.h \
    qttestqtcreatorprofilemaindialog.h \
    qttestqtcreatorprofilemenudialog.h \
    testqtcreatorprofilemenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestqtcreatorprofilemaindialog.ui \
    qttestqtcreatorprofilemenudialog.ui

RESOURCES += \
    ToolTestQtCreatorProFile.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtCreatorProFile/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt \
    zip.sh
