#!/bin/sh
valgrind --leak-check=full -v --show-reachable=yes --log-file=valgrind_memcheck.txt ../CppValgrindExample5-build-desktop/./CppValgrindExample5 --docroot=. --http-address=0.0.0.0 --http-port=8080 
