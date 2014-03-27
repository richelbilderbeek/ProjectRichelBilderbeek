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

#include "UnitFormMain.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include "UnitFormCorrect.h"
#include "UnitFormIncorrect.h"
#include "UnitFormAbout.h"
#include "UnitFormOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner), mQuestionGenerator(new QuestionGenerator(std::set<QuestionType>()))
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LabeledEdit1Enter(TObject *Sender)
{
  //User presses enter

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
  TFormOptions::SetDefaultOptions();
  mQuestionGenerator.reset(new QuestionGenerator(TFormOptions::mOptions));
  DrawScreen();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ControlAnswerKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key == VK_RETURN)
  {
    const bool isCorrect = mQuestionGenerator->GiveAnswer(ControlAnswer->Text.c_str());
    if (isCorrect)
    {
      std::auto_ptr<TFormCorrect> formCorrect(new TFormCorrect(0));
      formCorrect->ShowModal();
    }
    else
    {
      const std::vector<std::string> answers = mQuestionGenerator->GetAnswers();
      std::auto_ptr<TFormIncorrect> formIncorrect(new TFormIncorrect(0,answers));
      formIncorrect->ShowModal();
    }
    DrawScreen();
  }
}
//---------------------------------------------------------------------------
void TFormMain::DrawScreen()
{
  const std::string question = mQuestionGenerator->GetQuestion();
  ControlQuestion->Caption = question.c_str();
  ControlAnswer->Text = "";
  LabelCorrect->Caption = mQuestionGenerator->GetNcorrect();
  LabelIncorrect->Caption = mQuestionGenerator->GetNincorrect();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LabelQuitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LabelAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormAbout> formAbout(new TFormAbout(0));
  formAbout->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LabelOptionsClick(TObject *Sender)
{
  std::auto_ptr<TFormOptions> formOptions(new TFormOptions(0));
  formOptions->ShowModal();
  //Reset the Question Generator options
  mQuestionGenerator.reset(new QuestionGenerator(TFormOptions::mOptions));
  DrawScreen();

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ImageLetterSirconflexMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  const int letterIndex = (Y * 5) / ImageLetterSirconflex->Height;
  String s = "";
  switch (letterIndex)
  {
    case 0: s = "â"; break;
    case 1: s = "ê"; break;
    case 2: s = "î"; break;
    case 3: s = "ô"; break;
    case 4: s = "û"; break;
    default: assert(!"Should not get here"); break;
  }
  ControlAnswer->Text = ControlAnswer->Text + s;
}
//---------------------------------------------------------------------------

