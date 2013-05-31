//---------------------------------------------------------------------------
/*
  BeerWanter. A simple game.
  Copyright (C) 2005-2010 Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From hhtp://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include <nds.h>
#include "picbeer.h"

int main()
{
  //Initialization, thanks to http://dev-scene.com/NDS/Tutorials_Day_3
  //point our video buffer to the start of bitmap background video
  u16 * const video_buffer_main = BG_BMP_RAM(0);
  u16 * const video_buffer_sub  = BG_BMP_RAM_SUB(0);
  //set video mode to mode 5 with background 3 enabled
  videoSetMode(   MODE_5_2D | DISPLAY_BG3_ACTIVE);
  videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE);

  //map vram a to start of main background graphics memory
  vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
  vramSetBankC(VRAM_C_SUB_BG_0x06200000);

  //initialize the background
  BACKGROUND.control[3] = BG_BMP16_256x256 | BG_BMP_BASE(0);
  BACKGROUND.bg3_rotation.hdy = 0;
  BACKGROUND.bg3_rotation.hdx = 1 << 8;
  BACKGROUND.bg3_rotation.vdx = 0;
  BACKGROUND.bg3_rotation.vdy = 1 << 8;

  //initialize the sub background
  BACKGROUND_SUB.control[3] = BG_BMP16_256x256 | BG_BMP_BASE(0);
  BACKGROUND_SUB.bg3_rotation.hdy = 0;
  BACKGROUND_SUB.bg3_rotation.hdx = 1 << 8;
  BACKGROUND_SUB.bg3_rotation.vdx = 0;
  BACKGROUND_SUB.bg3_rotation.vdy = 1 << 8;

  const int maxx = SCREEN_WIDTH;
  const int maxy = SCREEN_HEIGHT;
  const PicBeer pic = PicBeer();
  int x = (maxx / 2) - (pic.GetWidth()  / 2);
  int y = (maxy / 2) - (pic.GetHeight() / 2);

  while(1)
  {
    //swiWaitForVBlank();
    pic.Draw(video_buffer_main,x,y);
    pic.Draw(video_buffer_sub,x,y);
    //Respond to keys
    scanKeys();
    const int held = keysHeld();
    if (held & KEY_RIGHT) { if (x + 1 + pic.GetWidth() < maxx) ++x; }
    if (held & KEY_LEFT) { --x; if (x<0) x=0; }
    if (held & KEY_DOWN) { if (y + 1 + pic.GetHeight() < maxy) ++y; }
    if (held & KEY_UP) { --y; if (y<0) y=0; }
    if (held & KEY_A) break;
    if (held & KEY_B) break;
    if (held & KEY_L) break;
    if (held & KEY_R) break;
  }
  systemShutDown();
}
