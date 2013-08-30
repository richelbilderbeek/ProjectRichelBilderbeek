QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
TEMPLATE = app

#For gprof
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
QMAKE_CXXFLAGS += -pg
QMAKE_LFLAGS += -pg

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtArrowItem \
  ../../Classes/CppQtHideAndShowDialog \
  ../../Classes/CppQtKeyboardFriendlyGraphicsView \
  ../../Classes/CppQtLabeledQuadBezierArrowItem \
  ../../Classes/CppQtPathArrowItem \
  ../../Classes/CppQtQuadBezierArrowItem \
  ../../Classes/CppQtRoundedRectItem \
  ../../Classes/CppQtRoundedTextRectItem \
  ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtArrowItem/qtarrowitem.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.cpp \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp \
    qtmain.cpp \
    qttestqtarrowitemsmaindialog.cpp \
    qttestqtarrowitemsmenudialog.cpp \
    testqtarrowitemsmenudialog.cpp \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.cpp \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtArrowItem/qtarrowitem.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.h \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h \
    ../../Classes/CppTrace/trace.h \
    qttestqtarrowitemsmaindialog.h \
    qttestqtarrowitemsmenudialog.h \
    testqtarrowitemsmenudialog.h \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.h \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtArrowItem/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt \
    ../../Classes/CppQtPathArrowItem/Licence.txt \
    ../../Classes/CppQtQuadBezierArrowItem/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppQtRoundedRectItem/Licence.txt \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/Licence.txt \
    ../../Classes/CppQtRoundedTextRectItem/Licence.txt

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestqtarrowitemsmaindialog.ui \
    qttestqtarrowitemsmenudialog.ui

RESOURCES += \
    ToolTestQtArrowItems.qrc
