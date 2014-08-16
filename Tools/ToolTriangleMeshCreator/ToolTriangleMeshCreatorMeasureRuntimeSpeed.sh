#!/bin/bash
set -u

FILE=../build-ToolTriangleMeshCreatorConsole-Desktop_Qt_5_1_1_MinGW_32bit-Release/release/ToolTriangleMeshCreatorConsole.exe
#FILE=../build-ToolTriangleMeshCreatorConsole-Desktop_Qt_5_1_1_MinGW_32bit-Debug/debug/ToolTriangleMeshCreatorConsole.exe

OUTPUT=ToolTriangleMeshCreatorMeasureRuntimeSpeedOutput.txt

echo "Start" > $OUTPUT


for n_layers in {1..10}
do
 #echo $n_layers >> $OUTPUT
 $FILE --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers $n_layers --fraction 0.9 --triangle_max_area 0.1 --triangle_min_angle 20.0 --profile >> $OUTPUT
done