#include <iostream>

int main()
{
  std::cout << "Hello World\n";
}

/* Output when calling 'crosscompiletowindows.sh':

richel@richel-laptop:~/GitHubs/richelbilderbeek/ProjectRichelBilderbeek/Test/CppMxeExample1$ ./crosscompiletowindows.sh 
Displaying cross compiler version (if it is not found, set the path to YourFolder/mxe/usr/bin
QMake version 3.0
Using Qt version 5.2.1 in /home/richel/GitHubs/richelbilderbeek/ProjectRichelBilderbeek/Libraries/mxe/usr/i686-pc-mingw32.static/qt5/lib
Cleaning up
rm: cannot remove ‘Makefile’: No such file or directory
rm: cannot remove ‘Makefile.*’: No such file or directory
rm: cannot remove ‘release’: No such file or directory
rm: cannot remove ‘debug’: No such file or directory
rm: cannot remove ‘ui_*.h’: No such file or directory
rm: cannot remove ‘qrc_*.cpp’: No such file or directory
rm: cannot remove ‘moc_*.cpp’: No such file or directory
rm: cannot remove ‘object_script*.*’: No such file or directory
rm: cannot remove ‘*.o’: No such file or directory
rm: cannot remove ‘*_plugin_import.cpp’: No such file or directory
Creating makefile
Project MESSAGE: Console application, built for Windows
Project MESSAGE: Console application, cross-compiling from Linux to Windows
Project MESSAGE: Console application, built for Windows
Project MESSAGE: Console application, cross-compiling from Linux to Windows
Project MESSAGE: Console application, built for Windows
Project MESSAGE: Console application, cross-compiling from Linux to Windows
Start make
make -f Makefile.Release
make[1]: Entering directory `/home/richel/GitHubs/richelbilderbeek/ProjectRichelBilderbeek/Test/CppMxeExample1'
i686-pc-mingw32.static-g++ -c -pipe -fno-keep-inline-dllexport -std=c++11 -Wall -Wextra -Weffc++ -O2 -frtti -Wall -Wextra -fexceptions -mthreads -DUNICODE -DNDEBUG -DNTRACE_BILDERBIKKEL -DQT_NO_DEBUG -DQT_CORE_LIB -I. -I'../../Libraries/mxe/usr/i686-pc-mingw32.static/qt5/include' -I'../../Libraries/mxe/usr/i686-pc-mingw32.static/qt5/include/QtCore' -I'release' -I'../../Libraries/mxe/usr/i686-pc-mingw32.static/qt5/mkspecs/win32-g++' -o release/main.o main.cpp
i686-pc-mingw32.static-g++ -Wl,-s -Wl,-subsystem,console -mthreads -o release/CppMxeExample1.exe release/main.o  -L/home/richel/GitHubs/richelbilderbeek/ProjectRichelBilderbeek/Libraries/mxe/usr/i686-pc-mingw32.static/qt5/lib -lQt5Core -lole32 -luuid -lws2_32 -ladvapi32 -lshell32 -luser32 -lkernel32 -lz -lsicuin -lsicuuc -lsicudt -lpcre16 
make[1]: Leaving directory `/home/richel/GitHubs/richelbilderbeek/ProjectRichelBilderbeek/Test/CppMxeExample1'
CppMxeExample1.pro, : SUCCESS
rm: cannot remove ‘ui_*.h’: No such file or directory
rm: cannot remove ‘qrc_*.cpp’: No such file or directory
rm: cannot remove ‘moc_*.cpp’: No such file or directory
rm: cannot remove ‘object_script*.*’: No such file or directory
rm: cannot remove ‘*.o’: No such file or directory
rm: cannot remove ‘*_plugin_import.cpp’: No such file or directory
richel@richel-laptop:~/GitHubs/richelbilderbeek/ProjectRichelBilderbeek/Test/CppMxeExample1$ 

*/