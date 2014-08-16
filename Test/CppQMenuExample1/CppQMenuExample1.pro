QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

SOURCES += \
    main.cpp \
    qmenuexample1widget.cpp

HEADERS += \
    qmenuexample1widget.h
