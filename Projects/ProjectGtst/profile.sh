#!/bin/sh
echo "Removing user file"
rm *.pro.user

echo "Creating profile executable"
qmake -config debug
make clean
make

echo "Removing makefile"
rm Makefile

echo "Removing object files"
rm *.o

echo "Start the application"
./gtst

echo "Analyse the gprof results"
gprof gtst > gprof.txt

echo "Remove temporary gprof file"
rm gmon.out

