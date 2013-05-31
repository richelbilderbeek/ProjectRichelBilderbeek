QT       += core gui
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtArrowItem \
    ../../Classes/CppQtDisplayPosItem \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView \
    ../../Classes/CppQtLeftRightRectItem \
    ../../Classes/CppQtPathArrowItem \
    ../../Classes/CppQtQuadBezierArrowItem \
    ../../Classes/CppQtRoundedEditRectItem \
    ../../Classes/CppQtRoundedRectItem \
    ../../Classes/CppQtRoundedTextRectItem \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtArrowItem/qtarrowitem.cpp \
    ../../Classes/CppQtDisplayPosItem/qtdisplaypositem.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp \
    ../../Classes/CppQtLeftRightRectItem/qtleftrightrectitem.cpp \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.cpp \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp \
    qtmain.cpp \
    qttestqtkeyboardfriendlygraphicsviewmenudialog.cpp \
    qttestqtkeyboardfriendlygraphicsviewwidget.cpp \
    testqtkeyboardfriendlygraphicsviewmenudialog.cpp \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtArrowItem/qtarrowitem.h \
    ../../Classes/CppQtDisplayPosItem/qtdisplaypositem.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h \
    ../../Classes/CppQtLeftRightRectItem/qtleftrightrectitem.h \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.h \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h \
    ../../Classes/CppTrace/trace.h \
    qttestqtkeyboardfriendlygraphicsviewmenudialog.h \
    qttestqtkeyboardfriendlygraphicsviewwidget.h \
    testqtkeyboardfriendlygraphicsviewmenudialog.h \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtArrowItem/Licence.txt \
    ../../Classes/CppQtDisplayPosItem/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt \
    ../../Classes/CppQtLeftRightRectItem/Licence.txt \
    ../../Classes/CppQtPathArrowItem/Licence.txt \
    ../../Classes/CppQtQuadBezierArrowItem/Licence.txt \
    ../../Classes/CppQtRoundedRectItem/Licence.txt \
    ../../Classes/CppQtRoundedTextRectItem/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    crosscompiletowindows.sh \
    Licence.txt \
    ../../Classes/CppQtRoundedEditRectItem/Licence.txt

FORMS += \
    qttestqtkeyboardfriendlygraphicsviewmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ToolTestQtKeyboardFriendlyGraphicsView.qrc
