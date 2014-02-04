include(../../Libraries/Boost.pri) #Or use the code below

QT += core gui
QT += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# undefined reference to `_imp___ZNK8QWebView8settingsEv'
greaterThan(QT_MAJOR_VERSION, 4): QT += webkitwidgets

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

TEMPLATE = app


SOURCES += \
    main.cpp \
    qtdialog.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

HEADERS += \
    qtdialog.h

FORMS += \
    qtdialog.ui

