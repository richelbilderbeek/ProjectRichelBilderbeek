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
#include "GameDasWahreSchlagerfestBeer32x32.h"
#include "GameDasWahreSchlagerfestBratwurst32x32.h"
#include "GameDasWahreSchlagerfestSmiley32x32.h"
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

  //mmLoad(MOD_69008_EXPERIENCE);
  //mmStart(MOD_69008_EXPERIENCE,MM_PLAY_LOOP);

}

void ribi::dws::NdsGameDialog::Display(const DasWahreSchlagerfestWidget& widget)
{
  const std::vector<std::vector<DasWahreSchlagerfestWidget::Tile>>& v = widget.GetTiles();
  assert(!v.empty());
  const int n_rows{static_cast<int>(v.size()   )};
  const int n_cols{static_cast<int>(v[0].size())};
  const int block_width {256 / n_cols};
  const int block_height{192 / n_rows};

  for (int row=0; row!=n_rows; ++row)
  {
    assert(row < static_cast<int>(v.size()));
    const std::vector<DasWahreSchlagerfestWidget::Tile>& line = v[row];
    assert(n_cols == static_cast<int>(line.size()));
    const int top = static_cast<int>(block_height * static_cast<double>(row  ));

    //dmaCopy(GameDasWahreSchlagerfestBeer32x32Tiles, VRAM_A, 32*32);

    for (int col=0; col!=n_cols; ++col)
    {
      const int left = static_cast<int>(block_width * static_cast<double>(col  ));
      switch (line[col])
      {
        case DasWahreSchlagerfestWidget::Tile::beer: PicBeer().Draw(VRAM_A,left,top); break;
        case DasWahreSchlagerfestWidget::Tile::bratwurst: PicBratwurst().Draw(VRAM_A,left,top); break;
        case DasWahreSchlagerfestWidget::Tile::empty: PicEmpty().Draw(VRAM_A,left,top); break;
        default: assert(!"Should not get here"); break;
      }
    }
  }
  //Draw cursor
  {
    const DasWahreSchlagerfestWidget::Cursor cursor = widget.GetCursor();
    const int x = cursor.x * block_width;
    const int y = cursor.y * block_height;
    switch (cursor.tile)
    {
      case DasWahreSchlagerfestWidget::Tile::beer: PicBeer().Draw(VRAM_A,x,y); break;
      case DasWahreSchlagerfestWidget::Tile::bratwurst: PicBratwurst().Draw(VRAM_A,x,y); break;
      case DasWahreSchlagerfestWidget::Tile::empty: PicEmpty().Draw(VRAM_A,x,y); break;
      default: assert(!"Should not get here"); break;
    }
  }
}

void ribi::dws::NdsGameDialog::OnChanged(const DasWahreSchlagerfestWidget& widget)
{
  Display(widget);
}

ribi::dws::Key ribi::dws::NdsGameDialog::RequestKey()
{
  while (1)
  {
    scanKeys(); //Don't forget!
    const int keys_down = keysDown();
    if (keys_down)
    {
      if (     keys_down & KEY_X     ) { return ribi::dws::Key::quit;  }
      else if (keys_down & KEY_RIGHT ) { return ribi::dws::Key::right; }
      else if (keys_down & KEY_DOWN  ) { return ribi::dws::Key::down;  }
      else if (keys_down & KEY_LEFT  ) { return ribi::dws::Key::left;  }
    }

    swiWaitForVBlank();
  }
}
