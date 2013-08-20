QT       += core gui widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

TEMPLATE = app

LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_regex \
  -lboost_system

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtHideAndShowDialog

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp\
    qtsitemapgeneratormaindialog.cpp \
    qtsitemapgeneratormenudialog.cpp \
    sitemapgeneratormenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    qtsitemapgeneratormaindialog.h \
    qtsitemapgeneratormenudialog.h \
    sitemapgeneratormenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtsitemapgeneratormaindialog.ui \
    qtsitemapgeneratormenudialog.ui

RESOURCES += \
    ToolRichelbilderbeekNlSitemapGenerator.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt
