// GOAL: using Boost and libnds

// FAILS:
/*


14:00:17: Running steps for project CppLibndsExample4...
14:00:17: Configuration unchanged, skipping qmake step.
14:00:17: Starting: "/usr/bin/make"
/home/richel/devkitPro/devkitARM/bin/arm-none-eabi-g++ -c -MMD -MP -MF -mm -g -mthumb -mthumb-interwork -g -Wall -W -fPIE -DARM9 -I../source -I. -I/home/richel/devkitPro/libnds/include -I/home/richel/devkitPro/devkitARM/arm-none-eabi/include -isystem /usr/include -isystem /usr/include/i386-linux-gnu -I/usr/lib/i386-linux-gnu/qt5/mkspecs/linux-g++ -o main.o ../source/main.cpp
In file included from /home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/bits/locale_facets.h:41:0,
                 from /home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/bits/basic_ios.h:37,
                 from /home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/ios:44,
                 from /home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/ostream:38,
                 from /home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/iostream:39,
                 from ../source/main.cpp:3:
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:46:35: error: '_U' was not declared in this scope
     static const mask upper     = _U;
                                   ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:47:32: error: '_L' was not declared in this scope
     static const mask lower  = _L;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:48:32: error: '_U' was not declared in this scope
     static const mask alpha  = _U | _L;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:48:37: error: '_L' was not declared in this scope
     static const mask alpha  = _U | _L;
                                     ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:49:32: error: '_N' was not declared in this scope
     static const mask digit  = _N;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:50:33: error: '_X' was not declared in this scope
     static const mask xdigit  = _X | _N;
                                 ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:50:38: error: '_N' was not declared in this scope
     static const mask xdigit  = _X | _N;
                                      ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:51:32: error: '_S' was not declared in this scope
     static const mask space  = _S;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:52:32: error: '_P' was not declared in this scope
     static const mask print  = _P | _U | _L | _N | _B;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:52:37: error: '_U' was not declared in this scope
     static const mask print  = _P | _U | _L | _N | _B;
                                     ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:52:42: error: '_L' was not declared in this scope
     static const mask print  = _P | _U | _L | _N | _B;
                                          ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:52:47: error: '_N' was not declared in this scope
     static const mask print  = _P | _U | _L | _N | _B;
                                               ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:52:52: error: '_B' was not declared in this scope
     static const mask print  = _P | _U | _L | _N | _B;
                                                    ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:53:32: error: '_P' was not declared in this scope
     static const mask graph  = _P | _U | _L | _N;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:53:37: error: '_U' was not declared in this scope
     static const mask graph  = _P | _U | _L | _N;
                                     ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:53:42: error: '_L' was not declared in this scope
     static const mask graph  = _P | _U | _L | _N;
                                          ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:53:47: error: '_N' was not declared in this scope
     static const mask graph  = _P | _U | _L | _N;
                                               ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:54:32: error: '_C' was not declared in this scope
     static const mask cntrl  = _C;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:55:32: error: '_P' was not declared in this scope
     static const mask punct  = _P;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:56:32: error: '_U' was not declared in this scope
     static const mask alnum  = _U | _L | _N;
                                ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:56:37: error: '_L' was not declared in this scope
     static const mask alnum  = _U | _L | _N;
                                     ^
/home/richel/devkitPro/devkitARM/arm-none-eabi/include/c++/4.9.2/arm-none-eabi/thumb/bits/ctype_base.h:56:42: error: '_N' was not declared in this scope
     static const mask alnum  = _U | _L | _N;
                                          ^
Makefile:384: recipe for target 'main.o' failed
make: *** [main.o] Error 1
14:00:18: The process "/usr/bin/make" exited with code 2.
Error while building/deploying project CppLibndsExample4 (kit: Desktop)
When executing step 'Make'
14:00:18: Elapsed time: 00:01.

*/

#include <nds.h>
#include <iostream>
#include <boost/signals2.hpp>

int main()
{
	PrintConsole topScreen;
	PrintConsole bottomScreen;
	
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);

  consoleInit(&topScreen,    3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
	consoleInit(&bottomScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);


	consoleSelect(&topScreen);
  std::cout
    << "01234567890123456789012345678901" //No newline needed
    << "1\n"
    << "2 TOP\n"
    << "3 SCREEN\n"
    << "4 HERE\n"
    << "5\n"
    << "6 32 chars wide, 23 chars high\n"
    << "7\n"
    << "8\n"
    << "9\n"
    << "0\n"
    << "1\n"
    << "2\n"
    << "3\n"
    << "4\n"
    << "5\n"
    << "6\n"
    << "7\n"
    << "8\n"
    << "9\n"
    << "0\n"
    << "1\n"
    << "2\n"
    << "34567890123456789012345678901234" //No newline needed
  ;

	consoleSelect(&bottomScreen);

  std::cout
    << "01234567890123456789012345678901" //No newline needed
    << "1\n"
    << "2 BOTTOM\n"
    << "3 SCREEN\n"
    << "4 HERE\n"
    << "5\n"
    << "6 32 chars wide, 23 chars high\n"
    << "7\n"
    << "8\n"
    << "9\n"
    << "0\n"
    << "1\n"
    << "2\n"
    << "3\n"
    << "4\n"
    << "5\n"
    << "6\n"
    << "7\n"
    << "8\n"
    << "9\n"
    << "0\n"
    << "1\n"
    << "2\n"
    << "34567890123456789012345678901234" //No newline needed
  ;

  while(1)
  {
		swiWaitForVBlank();
	}
}
