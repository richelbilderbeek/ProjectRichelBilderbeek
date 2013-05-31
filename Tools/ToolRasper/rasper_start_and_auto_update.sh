#!/bin/sh

WORKDIR=/home/pi/Projects/Tools/ToolRasper
MAKEFILE=$WORKDIR/Makefile

rm ToolRasperSource.zip
wget richelbilderbeek.nl/ToolRasperSource.zip
unzip -o ToolRasperSource.zip

touch $WORKDIR/ToolRasper.pro
qmake $WORKDIR/ToolRasper.pro -o $MAKEFILE

if [ -f $MAKEFILE ]
then
  echo "$WORKDIR created successfully"
else
  echo "$WORKDIR not created, now exiting script"
  exit
fi

make --makefile=$MAKEFILE --directory=$WORKDIR


chmod +x $WORKDIR/ToolRasper
$WORKDIR/ToolRasper


