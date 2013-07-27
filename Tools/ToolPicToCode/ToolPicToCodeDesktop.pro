QT       += core gui
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtSprites

SOURCES += qtmain.cpp\
    pictocodemaindialog.cpp \
    pictocodemenudialog.cpp \
    qtpictocodemaindialog.cpp \
    qtpictocodemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtSprites/qtsprites.cpp
HEADERS += \
    pictocodemaindialog.h \
    pictocodemenudialog.h \
    qtpictocodemaindialog.h \
    qtpictocodemenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtSprites/qtsprites.h
FORMS += \
    qtpictocodemaindialog.ui \
    qtpictocodemenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ToolPicToCode.qrc
