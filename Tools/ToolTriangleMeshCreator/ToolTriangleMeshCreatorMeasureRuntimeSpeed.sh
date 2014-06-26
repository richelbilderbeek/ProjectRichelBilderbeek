#!/bin/bash
set -u

#FILE=../build-ToolTriangleMeshCreatorConsole-Desktop_Qt_5_1_1_MinGW_32bit-Release/release/ToolTriangleMeshCreatorConsole.exe
FILE=../build-ToolTriangleMeshCreatorConsole-Desktop_Qt_5_1_1_MinGW_32bit-Debug/debug/ToolTriangleMeshCreatorConsole.exe

for num in 8.0 4.0 2.0 1.0 0.5 0.25
do
 echo "Number: $num"
 $FILE --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area $num --triangle_min_angle 20.0 --profile
done