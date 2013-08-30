QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog


SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    mazecreatormenudialog.cpp \
    qtmain.cpp \
    qtmazecreatormaindialog.cpp \
    qtmazecreatormenudialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    mazecreatormenudialog.h \
    qtmazecreatormaindialog.h \
    qtmazecreatormenudialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtmazecreatormaindialog.ui \
    qtmazecreatormenudialog.ui

RESOURCES += \
    mazecreator.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt
