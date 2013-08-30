QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView \
    ../../Classes/CppQtRoundedRectItem \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp \
    qtmain.cpp \
    qttestqtroundedrectitemmaindialog.cpp \
    qttestqtroundedrectitemmenudialog.cpp \
    testqtroundedrectitemmenudialog.cpp \
    qttestqtroundedrectitemwidget.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h \
    ../../Classes/CppTrace/trace.h \
    qttestqtroundedrectitemmaindialog.h \
    qttestqtroundedrectitemmenudialog.h \
    testqtroundedrectitemmenudialog.h \
    qttestqtroundedrectitemwidget.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt \
    ../../Classes/CppQtRoundedRectItem/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    R.png \
    ToolTestQtRoundedRectItemWelcome.png \
    zip.sh \
    Licence.txt

FORMS += \
    qttestqtroundedrectitemmaindialog.ui \
    qttestqtroundedrectitemmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ToolTestQtRoundedRectItem.qrc
