#!/bin/sh
valgrind --leak-check=full -v --show-reachable=yes --log-file=ProjectBrainweaverMemcheckDebug.txt ../build-ProjectBrainweaverDeveloper-Qt_5_0_1_qt5-Debug/./ProjectBrainweaverDeveloper
valgrind --leak-check=full -v --show-reachable=yes --log-file=ProjectBrainweaverMemcheckRelease.txt ../build-ProjectBrainweaverDeveloper-Qt_5_0_1_qt5-Release/./ProjectBrainweaverDeveloper
