QT       += core gui
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog


SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    daswahreschlagerfestmenudialog.cpp \
    daswahreschlagerfestwidget.cpp \
    qtdaswahreschlagerfestmaindialog.cpp \
    qtdaswahreschlagerfestmenudialog.cpp \
    qtdaswahreschlagerfestwidget.cpp \
    qtmain.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    daswahreschlagerfestwidget.h \
    qtdaswahreschlagerfestmaindialog.h \
    qtdaswahreschlagerfestmenudialog.h \
    qtdaswahreschlagerfestwidget.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtdaswahreschlagerfestmaindialog.ui \
    qtdaswahreschlagerfestmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt

RESOURCES += \
    GameDasWahreSchlagerfest.qrc
