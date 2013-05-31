#!/bin/sh
valgrind --tool=drd --log-file=drd.txt ../ProjectGtst-build-desktop/./gtst
