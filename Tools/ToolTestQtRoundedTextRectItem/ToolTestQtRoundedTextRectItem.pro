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
    ../../Classes/CppQtRoundedTextRectItem \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qttestqtroundedtextrectitemwidget.cpp \
    testqtroundedtextrectitemmenudialog.cpp \
    qttestqtroundedtextrectitemmenudialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qttestqtroundedtextrectitemmaindialog.cpp

HEADERS += \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qttestqtroundedtextrectitemwidget.h \
    testqtroundedtextrectitemmenudialog.h \
    ../../Classes/CppTrace/trace.h \
    qttestqtroundedtextrectitemmenudialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    qttestqtroundedtextrectitemmaindialog.h

OTHER_FILES += \
    ../../Classes/CppQtRoundedTextRectItem/Licence.txt \
    ../../Classes/CppQtRoundedRectItem/Licence.txt \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt \
    Licence.txt \
    crosscompiletowindows.sh \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestqtroundedtextrectitemmenudialog.ui \
    qttestqtroundedtextrectitemmaindialog.ui

RESOURCES += \
    ToolTestQtRoundedTextRectItem.qrc
