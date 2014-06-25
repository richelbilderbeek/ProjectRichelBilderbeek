#!/bin/bash
set -u

#FILE=../build-ToolTriangleMeshCreatorConsole-Desktop_Qt_5_1_1_MinGW_32bit-Release/release/ToolTriangleMeshCreatorConsole.exe
FILE=../build-ToolTriangleMeshCreatorConsole-Desktop_Qt_5_1_1_MinGW_32bit-Debug/debug/ToolTriangleMeshCreatorConsole.exe

#Easy
# $FILE --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area 10.0 --triangle_min_angle 20.0 --show_mesh --verbose

#Medium
$FILE --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area 1.0 --triangle_min_angle 20.0 --verbose

#Hard
#$FILE --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area 0.1 --triangle_min_angle 20.0 --verbose



