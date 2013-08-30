QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppPrimeExpert \
    ../../Classes/CppQtAboutDialog
SOURCES += main.cpp\
   testprimeexpertdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppPrimeExpert/primeexpert.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp
HEADERS  += \
    testprimeexpertdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppPrimeExpert/primeexpert.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h
FORMS += \
    testprimeexpertdialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
