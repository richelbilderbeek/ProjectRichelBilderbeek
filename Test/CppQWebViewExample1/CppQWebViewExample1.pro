QT += core gui

cross_compile {
  message(Crosscompiling)
}

greaterThan(QT_MAJOR_VERSION, 4) {
  message(Qt5)
  QT += widgets
  !cross_compile {
    message(Not crosscompiling)
    QT += webkitwidgets
  }
} else {
  message(Qt4)
  QT += webkit
}

TEMPLATE = app

SOURCES += \
  main.cpp\
  cppqwebviewexample1dialog.cpp

HEADERS  += cppqwebviewexample1dialog.h

FORMS    += cppqwebviewexample1dialog.ui
