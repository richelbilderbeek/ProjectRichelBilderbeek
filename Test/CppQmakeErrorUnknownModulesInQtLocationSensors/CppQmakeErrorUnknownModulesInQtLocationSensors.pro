QT += core gui

#To show I compile with Qt5
greaterThan(QT_MAJOR_VERSION, 4) {
  #Add webkitwidgets give the following error
  # :-1: error: Unknown module(s) in QT: location sensors
  QT += widgets webkitwidgets #Gives error
}
