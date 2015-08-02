// GOAL: using Qt and libnds
// FAILS: error "Qt has not been ported to this OS - see http://www.qt-project.org/"


#include <nds.h>
#include <iostream>
#include <QFile>

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
