QT += core gui

#To show I compile with Qt5
greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets webkitwidgets
}

# Solution:
#  sudo apt-get install libgstreamer1.0-dev
#  sudo apt-get install libgstreamer0.10-dev
#  sudo apt-get install libgstreamer-plugins-base1.0-dev
#  sudo apt-get install libgstreamer-plugins-base0.10-dev
