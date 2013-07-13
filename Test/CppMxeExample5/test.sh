#!/bin/sh
# Calls crosscompiletowindows and cleans up afterwards

./crosscompiletowindows.sh

rm Makefile*
#rm *.o
#rm -r release
#rm -r debug



