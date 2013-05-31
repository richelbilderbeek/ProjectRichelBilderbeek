#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

rm -r release
rm -r debug

echo "1. Cross compiling to Windows: console application version"

echo "1.1: Creating Windows makefile"
i686-pc-mingw32-qmake ProjectRichelBilderbeekConsole.pro

echo "1.2: making makefile"
make

echo "1.3: copying executable"
cp release/ProjectRichelBilderbeekConsole.exe .

echo "1.4: cleaning up"
rm -r release
rm -r debug

echo "2. Cross compiling to Windows: desktop application version"

echo "2.1: Creating Windows makefile"
i686-pc-mingw32-qmake ProjectRichelBilderbeekDesktop.pro

echo "2.2: making makefile"
make

echo "2.3: copying executable"
cp release/ProjectRichelBilderbeekDesktop.exe .

echo "2.4: cleaning up"
rm -r release
rm -r debug

echo "3. Cross compiling to Windows: web application version"

echo "3.1: Creating Windows makefile"
i686-pc-mingw32-qmake ProjectRichelBilderbeekWebsite.pro

echo "3.2: making makefile"
make

echo "3.3: copying executable"
cp release/ProjectRichelBilderbeekWebsite.exe .

echo "3.4: cleaning up"
rm -r release
rm -r debug

echo "4. Zipping the executables"
zip ProjectRichelBilderbeekExe.zip *.exe
