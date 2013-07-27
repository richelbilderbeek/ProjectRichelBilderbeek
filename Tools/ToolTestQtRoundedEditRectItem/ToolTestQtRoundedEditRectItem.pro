QT       += core gui
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView \
    ../../Classes/CppQtRoundedRectItem \
    ../../Classes/CppQtRoundedEditRectItem \
    ../../Classes/CppQtRoundedTextRectItem \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.cpp \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qttestqtroundededitrectitemwidget.cpp \
    testqtroundededitrectitemmenudialog.cpp \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp \
    qttestqtroundededitrectitemmenudialog.cpp \
    qttestqtroundededitrectitemmaindialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS += \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.h \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    qttestqtroundededitrectitemwidget.h \
    testqtroundededitrectitemmenudialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h \
    qttestqtroundededitrectitemmenudialog.h \
    qttestqtroundededitrectitemmaindialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

OTHER_FILES += \
    ../../Classes/CppQtRoundedEditRectItem/Licence.txt \
    ../../Classes/CppQtRoundedRectItem/Licence.txt \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt \
    Licence.txt \
    crosscompiletowindows.sh \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppQtRoundedTextRectItem/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestqtroundededitrectitemmenudialog.ui \
    qttestqtroundededitrectitemmaindialog.ui

RESOURCES += \
    ToolTestQtRoundedEditRectItem.qrc
