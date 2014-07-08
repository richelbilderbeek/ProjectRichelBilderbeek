#!/bin/sh
echo "Removing user file"
rm *.pro.user

echo "Creating profile executable"
qmake -config debug ToolTestPlaneDesktop.pro
make clean
make

echo "Removing makefile"
rm Makefile

echo "Removing object files"
rm *.o

echo "Start the application"
cd debug
./ToolTestPlaneDesktop.exe

echo "Analyse the gprof results"
gprof ToolTestPlaneDesktop.exe > gprof.txt

echo "Remove temporary gprof file"
rm gmon.out

