#include "ndsgamedialog.h"

#include <cassert>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include <stdio.h>

#include <nds.h>
#include <maxmod9.h>
//#include "soundbank.h"
//#include "soundbank_bin.h"
#include "picbeer.h"
#include "ndsgamedialog.h"

NdsGameDialog::NdsGameDialog()
  : m_key_pressed{-1},
    m_screen_bottom{}
{
  consoleDemoInit();
  videoSetMode(MODE_FB0);
  vramSetBankA(VRAM_A_LCD);

  //mmInitDefaultMem((mm_addr)soundbank_bin);


  consoleInit(&m_screen_bottom, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);


  consoleSelect(&m_screen_bottom);

  PicBeer().Draw(VRAM_A,0,0);
}

void NdsGameDialog::ProcessEvents()
{
  scanKeys(); //Don't forget!
  const int keys_down = keysDown();
  if (keys_down)
  {
    if (     keys_down & KEY_UP    ) { m_key_pressed =  0; }
    else if (keys_down & KEY_RIGHT ) { m_key_pressed =  1; }
    else if (keys_down & KEY_DOWN  ) { m_key_pressed =  2; }
    else if (keys_down & KEY_LEFT  ) { m_key_pressed =  3; }
    else if (keys_down & KEY_X     ) { m_key_pressed =  4; }
    else if (keys_down & KEY_A     ) { m_key_pressed =  5; }
    else if (keys_down & KEY_B     ) { m_key_pressed =  6; }
    else if (keys_down & KEY_Y     ) { m_key_pressed =  7; }
    else if (keys_down & KEY_L     ) { m_key_pressed =  8; }
    else if (keys_down & KEY_R     ) { m_key_pressed =  9; }
    else if (keys_down & KEY_START ) { m_key_pressed = 10; }
    else if (keys_down & KEY_SELECT) { m_key_pressed = 11; }
  }

  swiWaitForVBlank();
}
