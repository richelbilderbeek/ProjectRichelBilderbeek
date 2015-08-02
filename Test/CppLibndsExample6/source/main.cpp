
#include <nds.h>
#include <iostream>


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
    << "You are in the pub\n"
    << "What will you do?"
  ;

	consoleSelect(&bottomScreen);

  int charx = 1;
  int chary = 0;

  while(1)
  {
    consoleClear();

    std::cout
      << "[" << (charx == 1 && chary == 0 ? std::string("*") : std::string(" ")) << "] Sit at the bar\n"
      << "[" << (charx == 1 && chary == 1 ? std::string("*") : std::string(" ")) << "] Sit at a table\n"
      << "[" << (charx == 1 && chary == 2 ? std::string("*") : std::string(" ")) << "] Leave the pub\n"
    ;

    touchPosition touch;
    touchRead(&touch);
    if (touch.rawx != 0 && touch.rawy != 0)
    {
      charx = touch.px / 8; //A character is 8 pixels wide
      chary = touch.py / 8; //A character is 8 pixels wide
    }
    swiWaitForVBlank();
	}
}
