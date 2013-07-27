QT       += core gui
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog

SOURCES +=\
    qtmain.cpp \
    qtperfectelasticcollisionmaindialog.cpp \
    qtperfectelasticcollisionmenudialog.cpp \
    perfectelasticcollisionmenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp

HEADERS  += \
    qtperfectelasticcollisionmaindialog.h \
    qtperfectelasticcollisionmenudialog.h \
    perfectelasticcollisionmenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h

FORMS    += \
    qtperfectelasticcollisionmaindialog.ui \
    qtperfectelasticcollisionmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ToolPerfectElasticCollision.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    Licence.txt
