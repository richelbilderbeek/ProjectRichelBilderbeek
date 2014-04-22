#!/bin/sh
echo "Removing previous cachegrind files"
rm cachegrind.txt
rm cachegrind.out

echo "Start the application with cachegrind"
valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out --branch-sim=yes ../CppAddOne-build-desktop/./CppAddOne

echo "Converting cachegrind.out to cachegrind.txt using cg_annotate"
cg_annotate cachegrind.out > cachegrind.txt

echo "cachegrind done"

