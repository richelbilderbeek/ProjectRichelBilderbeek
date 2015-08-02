
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

  int pos = 0;
  while(1)
  {
    consoleClear();

    std::cout
      << "[" << (pos == 0 ? std::string("*") : std::string(" ")) << "] Sit at the bar\n"
      << "[" << (pos == 1 ? std::string("*") : std::string(" ")) << "] Sit at a table\n"
      << "[" << (pos == 2 ? std::string("*") : std::string(" ")) << "] Leave the pub\n"
    ;

    scanKeys();
    const int keys_down = keysDown();
    if (keys_down)
    {
      if (keys_down & KEY_DOWN) pos = (pos + 1    ) % 3;
      if (keys_down & KEY_UP) pos   = (pos - 1 + 3) % 3;
    }
    swiWaitForVBlank();
	}
}
