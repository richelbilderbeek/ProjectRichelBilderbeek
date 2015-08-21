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
#include "daswahreschlagerfestwidget.h"

ribi::dws::NdsGameDialog::NdsGameDialog()
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

  //mmLoad(MOD_69008_EXPERIENCE);
  //mmStart(MOD_69008_EXPERIENCE,MM_PLAY_LOOP);

}

ribi::dws::Key ribi::dws::NdsGameDialog::RequestKey()
{
  while (1)
  {
    scanKeys(); //Don't forget!
    const int keys_down = keysDown();
    if (keys_down)
    {
      if (     keys_down & KEY_UP    ) { return ribi::dws::Key::up; }
      else if (keys_down & KEY_RIGHT ) { return ribi::dws::Key::right; }
      else if (keys_down & KEY_DOWN  ) { return ribi::dws::Key::down; }
      else if (keys_down & KEY_LEFT  ) { return ribi::dws::Key::left; }
    }

    swiWaitForVBlank();
  }
}
