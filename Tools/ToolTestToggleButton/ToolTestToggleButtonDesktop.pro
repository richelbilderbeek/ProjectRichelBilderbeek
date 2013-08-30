QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtToggleButtonWidget \
  ../../Classes/CppRainbow \
  ../../Classes/CppRectangle \
  ../../Classes/CppTrace \
  ../../Classes/CppToggleButton \
  ../../Classes/CppToggleButtonWidget \
  ../../Classes/CppWidget

SOURCES += qtmain.cpp\
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    testtogglebuttonmenudialog.cpp \
    qttesttogglebuttonmaindialog.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp \
    qttesttogglebuttonmenudialog.cpp \
    ../../Classes/CppRainbow/rainbow.cpp

HEADERS  += \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    testtogglebuttonmenudialog.h \
    qttesttogglebuttonmaindialog.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h \
    ../../Classes/CppTrace/trace.h \
    qttesttogglebuttonmenudialog.h \
    ../../Classes/CppRainbow/rainbow.h

FORMS += \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttesttogglebuttonmaindialog.ui \
    qttesttogglebuttonmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppRectangle/Licence.txt \
    ../../Classes/CppToggleButton/Licence.txt \
    ../../Classes/CppToggleButtonWidget/Licence.txt \
    ../../Classes/CppWidget/Licence.txt \
    ../../Classes/CppQtToggleButtonWidget/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppRainbow/Licence.txt

RESOURCES += \
    ToolTestToggleButton.qrc
