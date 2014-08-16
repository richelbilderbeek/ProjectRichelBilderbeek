/*
  SimBrainiac, a simulation of Brainiacs interacting
  Copyright (C) 2008  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSimBrainiacMenu.h"
#include "UnitFormSimBrainiacMain.h"
#include "UnitFormSimBrainiacAbout.h"
#include "UnitFormSimBrainiacManual.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimBrainiacMenu *FormSimBrainiacMenu;
//---------------------------------------------------------------------------
__fastcall TFormSimBrainiacMenu::TFormSimBrainiacMenu(TComponent* Owner)
        : TForm(Owner)
{


}
//---------------------------------------------------------------------------
void __fastcall TFormSimBrainiacMenu::ButtonStartClick(TObject *Sender)
{
  std::auto_ptr<TFormSimBrainiacMain> f(new TFormSimBrainiacMain(
    0,
    PanelNbrainiacs->Caption.ToInt(),
    PanelNcorrectQuestionLevels->Caption.ToInt(),
    PanelNhasQuestionLevels->Caption.ToInt()
    ));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormSimBrainiacMenu::ImageNcorrectQuestionLevelsDownClick(
      TObject *Sender)
{
  const int n = PanelNcorrectQuestionLevels->Caption.ToInt();
  if (n > 1) PanelNcorrectQuestionLevels->Caption = IntToStr(n-1);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ImageNcorrectQuestionLevelsUpClick(
      TObject *Sender)
{
  const int n = PanelNcorrectQuestionLevels->Caption.ToInt();
  PanelNcorrectQuestionLevels->Caption = IntToStr(n+1);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ImageNhasQuestionLevelsDownClick(
      TObject *Sender)
{
  const int n = PanelNhasQuestionLevels->Caption.ToInt();
  if (n > 1) PanelNhasQuestionLevels->Caption = IntToStr(n-1);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ImageNhasQuestionLevelsUpClick(
      TObject *Sender)
{
  const int n = PanelNhasQuestionLevels->Caption.ToInt();
  PanelNhasQuestionLevels->Caption = IntToStr(n+1);

}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ButtonQuitClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ButtonAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormSimBrainiacAbout> f(new TFormSimBrainiacAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ButtonManualClick(TObject *Sender)
{
  std::auto_ptr<TFormSimBrainiacManual> f(new TFormSimBrainiacManual(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ImageNbrainiacsMinusClick(
      TObject *Sender)
{
  const int n = PanelNbrainiacs->Caption.ToInt();
  if (n > 100)
  {
    PanelNbrainiacs->Caption = IntToStr(n-100);
  }
  else if (n > 10)
  {
    PanelNbrainiacs->Caption = IntToStr(n-10);
  }
  else if (n > 1)
  {
    PanelNbrainiacs->Caption = IntToStr(n-1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormSimBrainiacMenu::ImageNbrainiacsPlusClick(
      TObject *Sender)
{
  const int n = PanelNbrainiacs->Caption.ToInt();
  if (n > 100)
  {
    PanelNbrainiacs->Caption = IntToStr(n+100);
  }
  else if (n > 10)
  {
    PanelNbrainiacs->Caption = IntToStr(n+10);
  }
  else
  {
    PanelNbrainiacs->Caption = IntToStr(n+1);
  }
}
//---------------------------------------------------------------------------

