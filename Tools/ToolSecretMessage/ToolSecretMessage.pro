QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace


SOURCES += \
    qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    secretmessagemenudialog.cpp \
    qtsecretmessagemenudialog.cpp \
    qtsecretmessagecreatedialog.cpp \
    qtsecretmessageextractdialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    secretmessagemenudialog.h \
    qtsecretmessagemenudialog.h \
    ../../Classes/CppTrace/trace.h \
    qtsecretmessagecreatedialog.h \
    qtsecretmessageextractdialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtsecretmessagemenudialog.ui \
    qtsecretmessagecreatedialog.ui \
    qtsecretmessageextractdialog.ui

RESOURCES += \
    ToolSecretMessage.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt
