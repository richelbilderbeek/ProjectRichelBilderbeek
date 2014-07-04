QT       += core gui
TARGET = CppQwtExample2
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

unix {
  QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
  LIBS += -lqwt
}

win32 {
  QMAKE_CXXFLAGS += -std=c++0x -Wall -Wextra
  INCLUDEPATH += E:/boost_1_50_0 C:/qwt-6.0.1/include

  LIBS += \
    -LE:/boost_1_50_0/stage/lib  \
    -lboost_system-mgw44-mt-1_50 \
    -lboost_filesystem-mgw44-mt-1_50 \
    -lboost_regex-mgw44-mt-1_50 \
    -LC:/qwt-6.0.1/lib \
    -lqwtd \ #Note: gives error 'QWidget: Must construct a QApplication before a QPaintDevice' when using '-lqwt'
    -lQtSvg
}

SOURCES += main.cpp \
    qtwidget.cpp \
    qwtplotitem.cpp \
    qwtplotwidget.cpp \
    qttextitem.cpp

HEADERS += \
    qtwidget.h \
    qwtplotitem.h \
    qwtplotwidget.h \
    qttextitem.h
