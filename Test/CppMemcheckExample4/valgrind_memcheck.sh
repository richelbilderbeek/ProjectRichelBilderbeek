#!/bin/sh
valgrind --leak-check=full -v --show-reachable=yes --log-file=valgrind_memcheck.txt ../CppValgrindExample4-build-desktop/./CppValgrindExample4
