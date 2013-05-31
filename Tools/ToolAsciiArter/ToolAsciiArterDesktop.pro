QT       += core gui
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppAsciiArter \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtHideAndShowDialog

SOURCES += qtmain.cpp \
  qtasciiartermaindialog.cpp \
  asciiartermaindialog.cpp \
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppAsciiArter/asciiarter.cpp \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    asciiartermenudialog.cpp \
    qtasciiartermenudialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += \
  qtasciiartermaindialog.h \
  asciiartermaindialog.h \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppAsciiArter/asciiarter.h \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    asciiartermenudialog.h \
    qtasciiartermenudialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS  += \
  qtasciiartermaindialog.ui \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtasciiartermenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppAsciiArter/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

RESOURCES += \
    ToolAsciiArter.qrc
