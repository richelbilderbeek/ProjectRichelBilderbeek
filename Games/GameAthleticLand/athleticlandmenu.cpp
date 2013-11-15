

#include <vcl.h>


#include "UnitFormGame.h"
#include "UnitFormMenu.h"


#pragma resource "*.dfm"
TFormMenu *FormMenu;

__fastcall TFormMenu::TFormMenu(TComponent* Owner)
        : TForm(Owner)
{
}

void __fastcall TFormMenu::PanelStartClick(TObject *Sender)
{
  boost::scoped_ptr<TFormGame> f(new TFormGame(0));
  f->ShowModal();
}


void __fastcall TFormMenu::TimerAutoStartTimer(TObject *Sender)
{
  TimerAutoStart->Enabled = false;
  PanelStartClick(0);
}


void __fastcall TFormMenu::PanelQuitClick(TObject *Sender)
{
  Close();        
}


