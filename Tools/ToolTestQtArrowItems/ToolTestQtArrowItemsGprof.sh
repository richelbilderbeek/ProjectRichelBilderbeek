#!/bin/bash
qmake -config release ToolTestQtArrowItems.pro
make clean
make
./ToolTestQtArrowItems
gprof ToolTestQtArrowItems > gprof.txt

