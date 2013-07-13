#!/bin/sh
#From http://richelbilderbeek.nl/CppMxe.htm

echo "Cross compiling to Windows"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake CppMxeExample5.pro

echo "2/2: making makefile"

make

echo "Done"
