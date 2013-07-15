#!/bin/bash
# Calls crosscompiletowindows and cleans up afterwards
myfile="crosscompiletowindows.sh"

if [ -e $myfile ]
then
  echo "'$myfile' found"
else
  echo "'$myfile' not found"
fi

./$myfile

rm Makefile*
rm *.o
#rm -r release
#rm -r debug



