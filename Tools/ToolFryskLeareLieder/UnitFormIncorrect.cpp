//---------------------------------------------------------------------------
/*
 *  Frysk Leare Lieder. A program to train the Frysian language.
 *  Copyright (C) 2007  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitFormIncorrect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormIncorrect *FormIncorrect;
//---------------------------------------------------------------------------
__fastcall TFormIncorrect::TFormIncorrect(TComponent* Owner,
          const std::vector<std::string>& answers)
        : TForm(Owner)
{
  const int nAnswers = answers.size();
  for (int i=0; i<nAnswers; ++i)
  {
    RichEdit1->Lines->Add(answers[i].c_str());

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormIncorrect::RichEdit1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormIncorrect::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  Close();        
}
//---------------------------------------------------------------------------
