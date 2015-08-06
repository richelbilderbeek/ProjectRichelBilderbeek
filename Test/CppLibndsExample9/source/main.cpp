 //Example that shows:
// - console at lower screen
// - graphics at top screen
// - use of STL

#include <nds.h>
#include <iostream>

int main()
{
  videoSetMode(MODE_0_2D);
  videoSetModeSub(MODE_0_2D);
  /*
  vramSetBankA(VRAM_A_MAIN_BG);
  vramSetBankC(VRAM_C_SUB_BG);

  bgExtPaletteEnable();
  bgExtPaletteEnableSub();
  */

  //consoleDemoInit();
  //videoSetMode(MODE_FB0);
  //vramSetBankA(VRAM_A_LCD);


  videoSetMode(   MODE_FB0); //Top to VRAM_A
  //videoSetModeSub(MODE_FB1); //Lower to VRAM_C
  vramSetBankA(VRAM_A_LCD);
  vramSetBankB(VRAM_B_LCD);

  //videoSetMode(MODE_0_2D);
  //videoSetModeSub(MODE_0_2D);
  //vramSetBankA(VRAM_A_MAIN_BG);
  //vramSetBankC(VRAM_C_SUB_BG);

  //vramSetBankA(VRAM_A_MAIN_BG);
  //vramSetBankC(VRAM_C_MAIN_BG);

  //The maximum x coordinat
  const int maxx = 256;
  //The maximum y coordinat
  const int maxy = 192;
  //The maximum R/G/B color value
  const int max_color = 32;
  //Counter for the scroll effect
  int z = 0;

  while(1)
  {
    //Respond to keys
    scanKeys();
    const int held = keysHeld();
    if (!held) continue;
    if (held & KEY_A) ++z;
    if (held & KEY_B) { --z; if (z<0) z+=max_color; }
    for (int y=0; y!=maxy; ++y)
    {
      for (int x=0; x!=maxx; ++x)
      {
        VRAM_A[(y*maxx)+x]
          = RGB15(
            (x+z  ) % max_color,
            (y+z  ) % max_color,
            (x+y+z) % max_color
          );
        VRAM_B[(y*maxx)+x] = RGB15((x+z  ) % max_color,(y+z  ) % max_color,(x+y+z) % max_color);
      }
    }
    swiWaitForVBlank();
  }
}
