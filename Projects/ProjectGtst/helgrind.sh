#!/bin/sh
valgrind --tool=helgrind --log-file=helgrind.txt ../ProjectGtst-build-desktop/./gtst --docroot=. --http-address=0.0.0.0 --http-port=8080
