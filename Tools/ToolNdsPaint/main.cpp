#include <cstdlib>
#include <iostream>

#include <nds.h>

int main()
{
  videoSetMode(MODE_FB0);
  vramSetBankA(VRAM_A_LCD);

  //notice we make sure the main graphics engine renders
  //to the lower lcd screen as it would be hard to draw if the
  //pixels did not show up directly beneath the pen
  //lcdMainOnBottom();
  int x = 0;
  int y = 0;
  int z = 0;

  while(1)
  {
    ++x;
    if (x == SCREEN_WIDTH )
    {
      x = 0; ++y;
      if (y == SCREEN_HEIGHT)
      {
        y = 0; z+=4;
        if (z == 32)  z = 0;
      }
    }

    //VRAM_A[x + y * SCREEN_WIDTH] = RGB15(z,z,z);

    scanKeys();
    const int keys = keysHeld();
    //if(keys & KEY_TOUCH)
    {
      //z = 0;
      // write the touchscreen coordinates in the touch variable

      touchPosition pos;
      touchRead(&pos);

      VRAM_A[pos.px + (pos.py * 256)] = rand();
      //VRAM_A[ std::rand() % (SCREEN_WIDTH * SCREEN_HEIGHT) ] = std::rand();
    }
  }

  return 0;
}
