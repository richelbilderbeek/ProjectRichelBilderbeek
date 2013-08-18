#!/bin/bash
qmake -config debug ProjectBrainweaverDeveloper.pro
make clean
make
./ProjectBrainweaverDeveloper
gprof ProjectBrainweaverDeveloper > gprof.txt

