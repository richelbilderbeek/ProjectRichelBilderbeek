//---------------------------------------------------------------------------
/*
  Leary Circumplex, tool to draw a Leary circumplex
  Copyright (C) 2009  Richèl Bilderbeek

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
#include <vcl.h>
#pragma hdrstop

#include "UnitFormMain.h"
#include "UnitFormDraw.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonDrawClick(TObject *Sender)
{
  const int n_scores = 8;
  boost::array<double,n_scores> scores;
  boost::array<std::string,n_scores> legend;
  for (int i=0; i!=n_scores; ++i)
  {
    legend[i] = Editor1->Cells[0][i+1].c_str();
    const double score = Editor1->Cells[1][i+1].ToDouble(); //+1 due to 1 fixed row
    scores[i] = score / 10.0; //In the Netherlands, scores range from [0.0,10.0]
  }

  form_leary.reset(new TFormDraw(0,scores,legend));
  form_leary->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonSaveClick(TObject *Sender)
{
  if (!form_leary) return;
  if (!SaveDialog1->Execute()) return;
  form_leary->ImageLeary->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("Image saved as " + SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();        
}
//---------------------------------------------------------------------------

