QT += core gui

#To show I compile with Qt5
greaterThan(QT_MAJOR_VERSION, 4) {
  #Add webkitwidgets give the following error under Lubuntu
  # :-1: error: Unknown module(s) in QT: location sensors
  #Under native Windows, however, this works fine
  QT += widgets webkitwidgets #Gives error under Lubuntu

}


# Solution provided by Xiao:
#   sudo apt-get install aptitude
#   sudo aptitude search sensors5|grep dev
#   sudo apt-get install qtsensors5-dev
#   sudo apt-get install qtsensors5-private-dev
#   sudo aptitude search location5|grep dev
#   sudo apt-get install qtlocation5-dev
#   sudo apt-get install qtlocation5-private-de

SOURCES += \
    main.cpp
