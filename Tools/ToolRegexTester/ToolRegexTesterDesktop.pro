QT       += core gui
TEMPLATE = app
LIBS += -lboost_regex
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp \
    qtregextestermaindialog.cpp \
    qtregextestermenudialog.cpp \
    regextesterboostmaindialog.cpp \
    regextestercpp11maindialog.cpp \
    regextestermaindialog.cpp \
    regextestermenudialog.cpp \
    regextesterqtmaindialog.cpp \
    regextestertr1maindialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppTrace/trace.h \
    qtregextestermaindialog.h \
    qtregextestermenudialog.h \
    regextesterboostmaindialog.h \
    regextestercpp11maindialog.h \
    regextestermaindialog.h \
    regextestermenudialog.h \
    regextesterqtmaindialog.h \
    regextestertr1maindialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtregextestermaindialog.ui \
    qtregextestermenudialog.ui

RESOURCES += \
    ToolRegexTester.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    crosscompiletowindows.sh \
    Licence.txt \
    zip.sh
