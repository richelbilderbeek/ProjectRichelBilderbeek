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

#include "UnitFormOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#include <cassert>
std::set<QuestionType> TFormOptions::mOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::ImageDoneClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::ImageVerbEasyClick(TObject *Sender)
{
  ImageVerbEasy->Tag = (ImageVerbEasy->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageVerbEasy->Canvas,0,0,ImageVerbEasy->Tag,true);
  ImageVerbEasy->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::ImageVerbMediumClick(TObject *Sender)
{
  ImageVerbMedium->Tag = (ImageVerbMedium->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageVerbMedium->Canvas,0,0,ImageVerbMedium->Tag,true);
  ImageVerbMedium->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ImageVerbHardClick(TObject *Sender)
{
  ImageVerbHard->Tag = (ImageVerbHard->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageVerbHard->Canvas,0,0,ImageVerbHard->Tag,true);
  ImageVerbHard->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ImageNounEasyClick(TObject *Sender)
{
  ImageNounEasy->Tag = (ImageNounEasy->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageNounEasy->Canvas,0,0,ImageNounEasy->Tag,true);
  ImageNounEasy->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ImageNounMediumClick(TObject *Sender)
{
  ImageNounMedium->Tag = (ImageNounMedium->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageNounMedium->Canvas,0,0,ImageNounMedium->Tag,true);
  ImageNounMedium->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ImageNounHardClick(TObject *Sender)
{
  ImageNounHard->Tag = (ImageNounHard->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageNounHard->Canvas,0,0,ImageNounHard->Tag,true);
  ImageNounHard->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ImageSentenceEasyClick(TObject *Sender)
{
  ImageSentenceEasy->Tag = (ImageSentenceEasy->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageSentenceEasy->Canvas,0,0,ImageSentenceEasy->Tag,true);
  ImageSentenceEasy->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ImageSentenceMediumClick(TObject *Sender)
{
  ImageSentenceMedium->Tag = (ImageSentenceMedium->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageSentenceMedium->Canvas,0,0,ImageSentenceMedium->Tag,true);
  ImageSentenceMedium->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ImageSentenceHardClick(TObject *Sender)
{
  ImageSentenceHard->Tag = (ImageSentenceHard->Tag == 0 ? 1 : 0);
  ImageList->Draw(ImageSentenceHard->Canvas,0,0,ImageSentenceHard->Tag,true);
  ImageSentenceHard->Refresh();
}
//---------------------------------------------------------------------------
void TFormOptions::SetDefaultOptions()
{
  mOptions.clear();
  assert(mOptions.size()==0);
  mOptions.insert(easyVerb);
  mOptions.insert(easyNoun);
  mOptions.insert(easySentence);
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::FormCreate(TObject *Sender)
{
  ImageVerbEasy->Tag   = ( mOptions.find(easyVerb)   != mOptions.end() ? 1 : 0);
  ImageVerbMedium->Tag = ( mOptions.find(mediumVerb) != mOptions.end() ? 1 : 0);
  ImageVerbHard->Tag   = ( mOptions.find(hardVerb)   != mOptions.end() ? 1 : 0);

  ImageNounEasy->Tag   = ( mOptions.find(easyNoun)   != mOptions.end() ? 1 : 0);
  ImageNounMedium->Tag = ( mOptions.find(mediumNoun) != mOptions.end() ? 1 : 0);
  ImageNounHard->Tag   = ( mOptions.find(hardNoun)   != mOptions.end() ? 1 : 0);

  ImageSentenceEasy->Tag   = ( mOptions.find(easySentence)   != mOptions.end() ? 1 : 0);
  ImageSentenceMedium->Tag = ( mOptions.find(mediumSentence) != mOptions.end() ? 1 : 0);
  ImageSentenceHard->Tag   = ( mOptions.find(hardSentence)   != mOptions.end() ? 1 : 0);

  ImageList->Draw(ImageVerbEasy->Canvas  ,0,0,ImageVerbEasy->Tag  ,true);
  ImageList->Draw(ImageVerbMedium->Canvas,0,0,ImageVerbMedium->Tag,true);
  ImageList->Draw(ImageVerbHard->Canvas  ,0,0,ImageVerbHard->Tag  ,true);
  ImageList->Draw(ImageNounEasy->Canvas  ,0,0,ImageNounEasy->Tag  ,true);
  ImageList->Draw(ImageNounMedium->Canvas,0,0,ImageNounMedium->Tag,true);
  ImageList->Draw(ImageNounHard->Canvas  ,0,0,ImageNounHard->Tag  ,true);
  ImageList->Draw(ImageSentenceEasy->Canvas  ,0,0,ImageSentenceEasy->Tag  ,true);
  ImageList->Draw(ImageSentenceMedium->Canvas,0,0,ImageSentenceMedium->Tag,true);
  ImageList->Draw(ImageSentenceHard->Canvas  ,0,0,ImageSentenceHard->Tag  ,true);

  ImageVerbEasy->Refresh();
  ImageVerbMedium->Refresh();
  ImageVerbHard->Refresh();
  ImageNounEasy->Refresh();
  ImageNounMedium->Refresh();
  ImageNounHard->Refresh();
  ImageSentenceEasy->Refresh();
  ImageSentenceMedium->Refresh();
  ImageSentenceHard->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  //Save to the std::set
  mOptions.clear();
  if (ImageVerbEasy->Tag==1) mOptions.insert(easyVerb);
  if (ImageVerbMedium->Tag==1) mOptions.insert(mediumVerb);
  if (ImageVerbHard->Tag==1) mOptions.insert(hardVerb);
  if (ImageNounEasy->Tag==1) mOptions.insert(easyNoun);
  if (ImageNounMedium->Tag==1) mOptions.insert(mediumNoun);
  if (ImageNounHard->Tag==1) mOptions.insert(hardNoun);
  if (ImageSentenceEasy->Tag==1) mOptions.insert(easySentence);
  if (ImageSentenceMedium->Tag==1) mOptions.insert(mediumSentence);
  if (ImageSentenceHard->Tag==1) mOptions.insert(hardSentence);
  //If none are selected, the easy verbs are selected 
  if (mOptions.empty()) mOptions.insert(easyVerb);
}
//---------------------------------------------------------------------------

