#!/bin/bash
FILE="/usr/include/qt5/QtCore/qglobal.h"
#FILE="/usr/include/qt4/QtCore/qglobal.h"
#FILE="/home/coen/Qt5.2.1/5.2.1/gcc_64/include/QtCore/qglobal.h"
#FILE="test.txt"

echo "#pragma GCC diagnostic ignored \"-Weffc++\""|cat - $FILE > /tmp/out && mv /tmp/out $FILE
echo "#pragma GCC diagnostic push"|cat - $FILE > /tmp/out && mv /tmp/out $FILE
echo "#pragma GCC diagnostic pop" >> $FILE


