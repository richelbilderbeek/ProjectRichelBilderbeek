#!/bin/bash
qmake -config release ProjectBrainweaverDeveloper.pro
make clean
make
./ProjectBrainweaverDeveloper
gprof ProjectBrainweaverDeveloper > gprof.txt

