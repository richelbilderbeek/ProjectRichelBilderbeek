#!/bin/sh
#echo "Removing user file"
rm *.pro.user

echo "Creating profile executable"

#Yes, must use '-config debug', otherwise gprof gives the following error:
#  'file './ToolTriangleMeshCreatorConsole.exe' has no symbols'
qmake -config debug ToolTriangleMeshCreatorConsole.pro

#make clean

make

#rm Makefile
#echo "Removing makefile"

#echo "Removing object files"
#rm *.o

echo "Start the application"
cd debug
./ToolTriangleMeshCreatorConsole.exe --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area 1.0 --triangle_min_angle 20.0 --profile

echo "Analyse the gprof results"
gprof ./ToolTriangleMeshCreatorConsole.exe > gprof.txt

echo "Remove temporary gprof file"
rm gmon.out

