#!/bin/sh
echo "Removing user file"
rm *.pro.user

#echo "Creating profile executable (debug mode)"
#qmake -config debug

echo "Creating profile executable (release mode)"
qmake -config release

make clean
make

echo "Removing makefile"
rm Makefile

echo "Removing object files"
rm *.o

echo "Start the application"
./CppGprofQtCreatorExample2

echo "Analyse the gprof results"
gprof CppGprofQtCreatorExample2 > gprof.txt

echo "Remove temporary gprof file"
rm gmon.out


