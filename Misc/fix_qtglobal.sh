#!/bin/bash
FILE="/usr/include/qt5/QtCore/qglobal.h"
#FILE="test.txt"

echo "#pragma GCC diagnostic ignored \"-Weffc++\""|cat - $FILE > /tmp/out && mv /tmp/out $FILE
echo "#pragma GCC diagnostic push"|cat - $FILE > /tmp/out && mv /tmp/out $FILE
echo "#pragma GCC diagnostic pop" >> $FILE
