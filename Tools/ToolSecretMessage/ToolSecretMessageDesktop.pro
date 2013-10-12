QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace


SOURCES += \
    qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    secretmessagemenudialog.cpp \
    qtsecretmessagemenudialog.cpp \
    qtsecretmessagecreatedialog.cpp \
    qtsecretmessageextractdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    secretmessagemaindialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    secretmessagemenudialog.h \
    qtsecretmessagemenudialog.h \
    ../../Classes/CppTrace/trace.h \
    qtsecretmessagecreatedialog.h \
    qtsecretmessageextractdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    secretmessagemaindialog.h

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
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
