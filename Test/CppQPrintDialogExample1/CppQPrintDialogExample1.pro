QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}

TEMPLATE = app

SOURCES += main.cpp\
        qtdialog.cpp

HEADERS  += qtdialog.h

FORMS    += qtdialog.ui
