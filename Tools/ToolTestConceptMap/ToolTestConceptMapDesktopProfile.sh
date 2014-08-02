#!/bin/sh
set -u

FILE=ToolTestConceptMapDesktop

echo "Removing user file"
rm *.pro.user

echo "Creating profile executable (note: this must enable debug mode, add NDEBUG and NTRACE_BILDERBIKKEL to get a release build)"
qmake -config debug $FILE.pro

#make clean
make

#echo "Removing makefile"
#rm Makefile

#echo "Removing object files"
#rm *.o

echo "Start the application"
./$FILE

echo "Analyse the gprof results"
gprof $FILE > $FILE.txt

echo "Remove temporary gprof file"
rm gmon.out
