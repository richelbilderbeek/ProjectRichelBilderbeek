#!/bin/sh
valgrind --leak-check=full -v --show-reachable=yes --log-file=memcheck.txt ../ProjectGtst-build-desktop/./gtst
