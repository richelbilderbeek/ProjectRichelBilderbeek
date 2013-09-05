#include "radio.h"

int main()
{

}

/* Compiler output:

15:38:36: Running steps for project CppHeaderFile...
15:38:36: Configuration unchanged, skipping qmake step.
15:38:36: Starting: "/usr/bin/make" -w
make: Entering directory `/home/richel/Projects/Test/CppHeaderFile-build-desktop-Qt_4_8_1__System__Release'
g++ -c -pipe -Wall -Wextra -Weffc++ -O2 -Wall -W -DQT_WEBKIT -I/usr/share/qt4/mkspecs/linux-g++ -I../CppHeaderFile -I../CppHeaderFile -I. -o main.o ../CppHeaderFile/main.cpp
In file included from ../CppHeaderFile/main.cpp:1:0:
../CppHeaderFile/radio.h:6:12: warning: 'LENGTH' initialized and declared 'extern' [enabled by default]
../CppHeaderFile/radio.h:29:15: error: conflicting declaration 'double Radio::S_PI'
../CppHeaderFile/radio.h:14:25: error: 'Radio::S_PI' has a previous declaration as 'const double Radio::S_PI'
../CppHeaderFile/radio.h:29:15: error: declaration of 'const double Radio::S_PI' outside of class is not definition [-fpermissive]
../CppHeaderFile/radio.h:31:5: error: redefinition of 'int Radio::size() const'
../CppHeaderFile/radio.h:22:12: error: 'int Radio::size() const' previously defined here
../CppHeaderFile/radio.h:8:12: warning: 'y' defined but not used [-Wunused-variable]
../CppHeaderFile/radio.h:9:13: warning: 'void func()' defined but not used [-Wunused-function]
make: Leaving directory `/home/richel/Projects/Test/CppHeaderFile-build-desktop-Qt_4_8_1__System__Release'
make: *** [main.o] Error 1
15:38:36: The process "/usr/bin/make" exited with code 2.
Error while building/deploying project CppHeaderFile (target: Desktop)
When executing step 'Make'

*/
