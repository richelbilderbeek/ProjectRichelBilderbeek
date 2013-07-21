QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
  message(Qt5)
  #Add webkitwidgets give the following error
  # :-1: error: Unknown module(s) in QT: location sensors
  QT += widgets webkitwidgets #Gives error
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
