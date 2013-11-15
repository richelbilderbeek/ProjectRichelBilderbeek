

#include <vcl.h>


#include "athleticlandbackground.h"
#include "UnitCreateAreas.h"
#include "UnitFormGame.h"
#include "athleticlandplayer.h"


#pragma resource "*.dfm"
TFormGame *FormGame;

__fastcall TFormGame::TFormGame(TComponent* Owner)
  : TForm(Owner),
    m_areas(CreateAreas()),
    m_cur_area(m_areas.begin()),
    m_n_lives(3)
{
  assert(&(m_areas[0]) == &(*m_cur_area));
  NewArea();
}

void TFormGame::NewArea() //call when m_cur_area has changed
{
  m_cur_area->InitBuffer(ImageBuffer);
  m_cur_area->Start();
}

void __fastcall TFormGame::TimerMainTimer(TObject *Sender)
{
  //Press player keys
  //One can move either left or right
  if (m_keys.count(VK_RIGHT )==1) m_cur_area->PressKeyRight();
  else if (m_keys.count(VK_LEFT)==1) m_cur_area->PressKeyLeft();
  //One can always start jumping
  if (m_keys.count(VK_SPACE)==1) m_cur_area->PressKeyJump();
  //One can always stop pressing keys
  if (m_keys.count(VK_LEFT )
    + m_keys.count(VK_RIGHT)
    + m_keys.count(VK_SPACE)==0) m_cur_area->PressNoKey();

  //Tick sprites and player
  //m_form->Tick();
  m_cur_area->Tick();

  //Draw background, sprites and player
  m_cur_area->Draw(ImageBuffer);

  //Check for game over
  if (m_cur_area->HasDied())
  {
    //Show player suffering or something like...
    //TODO
    --m_n_lives;
    //Is player game over?
    //TODO
    //Restart area
    m_cur_area->AddPlayer();
    m_cur_area->Restart();
  }
  //Check for finishing of game
  if (m_cur_area->HasFinished())
  {
    ++m_cur_area;
    if (m_cur_area == m_areas.end())
    {
      //ShowMessage("Game ended");
      m_cur_area = m_areas.begin();
    }
    NewArea();
  }



  //Draw buffer to screen
  //this->Canvas->Draw(0,0,m_form->ImageBuffer->Picture->Graphic);
  this->Canvas->StretchDraw(ClientRect,ImageBuffer->Picture->Graphic);
  //this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);

}

void __fastcall TFormGame::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  m_keys.insert(Key);

  if (m_keys.count(VK_LEFT) + m_keys.count(VK_RIGHT) == 2)
  {
    m_keys.erase(VK_LEFT);
    m_keys.erase(VK_RIGHT);
  }
}

void __fastcall TFormGame::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  m_keys.erase(Key);
}

