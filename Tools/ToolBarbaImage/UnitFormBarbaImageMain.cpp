//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
  Copyright (C) 2008  Richèl Bilderbeek

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
#include <cmath>
#include <stdexcept>
#include <cassert>
#include <boost/scoped_ptr.hpp>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormBarbaImageMain.h"
#include "UnitFormImage.h"
#include "UnitFunctions.h"
#include "UnitFormTrackBar.h"
#include "UnitFormBarbaImageAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBarbaImageMain *FormBarbaImageMain;
//---------------------------------------------------------------------------
__fastcall TFormBarbaImageMain::TFormBarbaImageMain(TComponent* Owner)
        : TForm(Owner), mChildIndex(0)
{
  this->Left   =  Screen->Width  / 8;
  this->Width  = (Screen->Width  / 8) * 6;
  this->Top    =  Screen->Height / 8;
  this->Height = (Screen->Height / 8) * 6;

  //Create the first window
  ItemCreateWindowClick(0);
}
//---------------------------------------------------------------------------
TFormImage * const TFormBarbaImageMain::CreateFormImage()
{
  //Create a new child form
  //TForm takes responsibility for deleting its children (automatically)
  TFormImage * const form = new TFormImage(this,this);
  assert(form!=0 && "form cannot be allocated");
  if (form==0) throw std::runtime_error("form cannot be allocated");
  //Create an indexed caption on the new form
  form->Caption = String("#") + String(mChildIndex);
  ++mChildIndex;
  //Store the form
  mChildren.push_back(form);
  return form;
}
//---------------------------------------------------------------------------
void __fastcall TFormBarbaImageMain::ItemCreateWindowClick(TObject *Sender)
{
  TFormImage * const form = CreateFormImage();
  form->ClientWidth  = 200;
  form->ClientHeight = 200;
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::AddColoredNoise(TFormImage * const formSource)
{
  TFormImage * const formTarget = CreateFormImage();
  //Set the size of child form same as formSource
  formTarget->Width  = formSource->Width;
  formTarget->Height = formSource->Height;
  //Create a TrackBar form
  TFormTrackBar * formTrackBar
    = new TFormTrackBar( this,formSource->Image,formTarget,bikkel::AddColoredNoise);
  //Remember old form positions
  const TRect sourceRect = GetWindowRect(formSource);
  const TRect targetRect = GetWindowRect(formTarget);
  //Arrange all forms
  formTrackBar->Left = 0;
  formTrackBar->Top = 0;
  formTrackBar->Width = Screen->Width;
  formTrackBar->TrackBar->Frequency = 16;
  formTrackBar->TrackBar->Max = 255;
  formSource->Left   = 0;
  formSource->Width  = Screen->Width / 2;
  formSource->Top    = formTrackBar->Height;
  formSource->Height = Screen->Height - formTrackBar->Height;
  formTarget->Left   = formSource->Width;
  formTarget->Width  = formSource->Width;
  formTarget->Top    = formSource->Top;
  formTarget->Height = formSource->Height;
  formTarget->Image->Picture = formSource->Image->Picture;
  formTarget->Image->Visible = true;
  assert(formTrackBar->Visible == false && "Cannot do ShowModal on a visible window");
  formTrackBar->ShowModal();
  formTarget->SetAllEnabled();
  //Set the old position back
  SetWindowRect(formSource,sourceRect);
  SetWindowRect(formTarget,targetRect);
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::Bleach(TFormImage * const formSource)
{
  TFormImage * const formTarget = CreateFormImage();
  //Set the size of child form same as formSource
  formTarget->Width  = formSource->Width;
  formTarget->Height = formSource->Height;
  //Create a TrackBar form
  TFormTrackBar * formTrackBar
    = new TFormTrackBar(this,formSource->Image,formTarget,bikkel::Bleach);
  //Remember old form positions
  const TRect sourceRect = GetWindowRect(formSource);
  const TRect targetRect = GetWindowRect(formTarget);
  //Arrange all forms
  formTrackBar->Left = 0;
  formTrackBar->Top = 0;
  formTrackBar->Width = Screen->Width;
  formTrackBar->TrackBar->Frequency = 16;
  formTrackBar->TrackBar->Max = 255;
  formSource->Left   = 0;
  formSource->Width  = Screen->Width / 2;
  formSource->Top    = formTrackBar->Height;
  formSource->Height = Screen->Height - formTrackBar->Height;
  formTarget->Left   = formSource->Width;
  formTarget->Width  = formSource->Width;
  formTarget->Top    = formSource->Top;
  formTarget->Height = formSource->Height;
  formTarget->Image->Picture = formSource->Image->Picture;
  formTarget->Image->Visible = true;
  assert(formTrackBar->Visible == false && "Cannot do ShowModal on a visible window");
  formTrackBar->ShowModal();
  formTarget->SetAllEnabled();
  //Set the old position back
  SetWindowRect(formSource,sourceRect);
  SetWindowRect(formTarget,targetRect);
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::Darken(TFormImage * const formSource)
{
  TFormImage * const formTarget = CreateFormImage();
  //Set the size of child form same as formSource
  formTarget->Width  = formSource->Width;
  formTarget->Height = formSource->Height;
  //Create a TrackBar form
  TFormTrackBar * formTrackBar
    = new TFormTrackBar(this,formSource->Image,formTarget,bikkel::Darken);
  //Remember old form positions
  const TRect sourceRect = GetWindowRect(formSource);
  const TRect targetRect = GetWindowRect(formTarget);
  //Arrange all forms
  formTrackBar->Left = 0;
  formTrackBar->Top = 0;
  formTrackBar->Width = Screen->Width;
  formTrackBar->TrackBar->Frequency = 16;
  formTrackBar->TrackBar->Max = 255;
  formSource->Left   = 0;
  formSource->Width  = Screen->Width / 2;
  formSource->Top    = formTrackBar->Height;
  formSource->Height = Screen->Height - formTrackBar->Height;
  formTarget->Left   = formSource->Width;
  formTarget->Width  = formSource->Width;
  formTarget->Top    = formSource->Top;
  formTarget->Height = formSource->Height;
  formTarget->Image->Picture = formSource->Image->Picture;
  formTarget->Image->Visible = true;
  assert(formTrackBar->Visible == false && "Cannot do ShowModal on a visible window");
  formTrackBar->ShowModal();
  formTarget->SetAllEnabled();
  //Set the old position back
  SetWindowRect(formSource,sourceRect);
  SetWindowRect(formTarget,targetRect);
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::DoHistogramEqualization(const TImage * const source)
{
  TFormImage * const formNew = CreateFormImage();
  bikkel::DoHistogramEqualization(source,formNew->Image);
  formNew->ClientWidth  = formNew->Image->Picture->Bitmap->Width;
  formNew->ClientHeight = formNew->Image->Picture->Bitmap->Height;
  formNew->SetAllEnabled();
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::EnhanceContrast(const TImage * const source)
{
  TFormImage * const formNew = CreateFormImage();
  formNew->Image->Picture = source->Picture;
  bikkel::EnhanceContrast(formNew->Image);
  formNew->ClientWidth  = formNew->Image->Picture->Bitmap->Width;
  formNew->ClientHeight = formNew->Image->Picture->Bitmap->Height;
  formNew->SetAllEnabled();
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::ConvertToGrey(const TImage * const source)
{
  TFormImage * const formNew = CreateFormImage();
  bikkel::ConvertToGrey(source,formNew->Image);
  formNew->ClientWidth  = formNew->Image->Picture->Bitmap->Width;
  formNew->ClientHeight = formNew->Image->Picture->Bitmap->Height;
  formNew->SetAllEnabled();
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::ThresholdFilterColor(TFormImage * const formSource)
{
  TFormImage * const formTarget = CreateFormImage();
  //Set the size of child form same as formSource
  formTarget->Width  = formSource->Width;
  formTarget->Height = formSource->Height;
  //Create a TrackBar form
  TFormTrackBar * formTrackBar
    = new TFormTrackBar(this,formSource->Image,formTarget,bikkel::ThresholdFilterColor);
  //Remember old form positions
  const TRect sourceRect = GetWindowRect(formSource);
  const TRect targetRect = GetWindowRect(formTarget);
  //Arrange all forms
  formTrackBar->Left = 0;
  formTrackBar->Top = 0;
  formTrackBar->Width = Screen->Width;
  formTrackBar->TrackBar->Frequency = 16;
  formTrackBar->TrackBar->Max = 255;
  formSource->Left   = 0;
  formSource->Width  = Screen->Width / 2;
  formSource->Top    = formTrackBar->Height;
  formSource->Height = Screen->Height - formTrackBar->Height;
  formTarget->Left   = formSource->Width;
  formTarget->Width  = formSource->Width;
  formTarget->Top    = formSource->Top;
  formTarget->Height = formSource->Height;
  formTarget->Image->Picture = formSource->Image->Picture;
  formTarget->Image->Visible = true;
  assert(formTrackBar->Visible == false && "Cannot do ShowModal on a visible window");
  formTrackBar->ShowModal();
  formTarget->SetAllEnabled();
  //Set the old position back
  SetWindowRect(formSource,sourceRect);
  SetWindowRect(formTarget,targetRect);
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::ThresholdFilterNoColor(TFormImage * const formSource)
{
  TFormImage * const formTarget = CreateFormImage();
  //Set the size of child form same as formSource
  formTarget->Width  = formSource->Width;
  formTarget->Height = formSource->Height;
  //Create a TrackBar form
  TFormTrackBar * formTrackBar
    = new TFormTrackBar(this,formSource->Image,formTarget,bikkel::ThresholdFilterNoColor);
  //Remember old form positions
  const TRect sourceRect = GetWindowRect(formSource);
  const TRect targetRect = GetWindowRect(formTarget);
  //Arrange all forms
  formTrackBar->Left = 0;
  formTrackBar->Top = 0;
  formTrackBar->Width = Screen->Width;
  formTrackBar->TrackBar->Frequency = 16;
  formTrackBar->TrackBar->Max = 255;
  formSource->Left   = 0;
  formSource->Width  = Screen->Width / 2;
  formSource->Top    = formTrackBar->Height;
  formSource->Height = Screen->Height - formTrackBar->Height;
  formTarget->Left   = formSource->Width;
  formTarget->Width  = formSource->Width;
  formTarget->Top    = formSource->Top;
  formTarget->Height = formSource->Height;
  formTarget->Image->Picture = formSource->Image->Picture;
  formTarget->Image->Visible = true;
  assert(formTrackBar->Visible == false && "Cannot do ShowModal on a visible window");
  formTrackBar->ShowModal();
  formTarget->SetAllEnabled();
  //Set the old position back
  SetWindowRect(formSource,sourceRect);
  SetWindowRect(formTarget,targetRect);
}
//---------------------------------------------------------------------------
const TRect GetWindowRect(const TForm * const form)
{
  return
    TRect( TPoint(form->Left              , form->Top               ),
           TPoint(form->Left + form->Width, form->Top + form->Height) );
}
//---------------------------------------------------------------------------
void SetWindowRect(TForm * const form, const TRect& rect)
{
  form->Left   = rect.Left;
  form->Top    = rect.Top;
  form->Width  = rect.Width();
  form->Height = rect.Height();
}
//---------------------------------------------------------------------------
void __fastcall TFormBarbaImageMain::ItemCascadeClick(TObject *Sender)
{
  const int windowTopBorderHeight = 30;
  const int windowLeftBorderWidth =  4;

  int x = Left + windowLeftBorderWidth;
  int y = Top  + windowTopBorderHeight;
  const int nWindows = mChildren.size();
  for (int i=0; i!=nWindows; ++i, x+=16, y+=16)
  {
    mChildren[i]->Left = x;
    mChildren[i]->Top  = y;
    mChildren[i]->SetFocus();
  }
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::RemoveMe(TFormImage * const formImage)
{
  const int index
    = std::find(mChildren.begin(),mChildren.end(),formImage)
    - mChildren.begin();
  assert(index < static_cast<int>(mChildren.size() ) );
  mChildren[index] = mChildren.back();
  mChildren.pop_back();
}
//---------------------------------------------------------------------------
void __fastcall TFormBarbaImageMain::ItemTileClick(TObject *Sender)
{
  const int windowTopBorderHeight = 30;
  const int windowLeftBorderWidth =  4;

  const int nWindows = mChildren.size();
  if (nWindows == 0) return;
  const int borderSize = 8;
  if (nWindows == 1)
  {
    mChildren[0]->Left   = Left + windowLeftBorderWidth + borderSize;
    mChildren[0]->Width  = ClientWidth  - (2 * borderSize);
    mChildren[0]->Top    = Top + windowTopBorderHeight + borderSize;
    mChildren[0]->Height = ClientHeight - (2 * borderSize);
    return;
  }
  const int nCols = 1 + static_cast<int>( std::sqrt( static_cast<double>(nWindows - 1) ) );
  const int width  = (ClientWidth  - (2 * borderSize)) / nCols;
  const int height = (ClientHeight - (2 * borderSize)) / nCols; //nCols == nRows
  for (int i=0; i!=nWindows; ++i)
  {
    const int x = Left + windowLeftBorderWidth + borderSize + ((i%nCols) * width );
    const int y = Top  + windowTopBorderHeight + borderSize + ((i/nCols) * height);
    mChildren[i]->Left   = x;
    mChildren[i]->Top    = y;
    mChildren[i]->Width  = width;
    mChildren[i]->Height = height;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormBarbaImageMain::ItemAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormBarbaImageAbout> form(new TFormBarbaImageAbout(0));
  form->ShowModal();
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::ExtractBlue(const TImage * const source)
{
  TFormImage * const formNew = CreateFormImage();
  bikkel::ExtractBlue(source,formNew->Image);
  formNew->ClientWidth  = formNew->Image->Picture->Bitmap->Width;
  formNew->ClientHeight = formNew->Image->Picture->Bitmap->Height;
  formNew->SetAllEnabled();
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::ExtractGreen(const TImage * const source)
{
  TFormImage * const formNew = CreateFormImage();
  bikkel::ExtractGreen(source,formNew->Image);
  formNew->ClientWidth  = formNew->Image->Picture->Bitmap->Width;
  formNew->ClientHeight = formNew->Image->Picture->Bitmap->Height;
  formNew->SetAllEnabled();
}
//---------------------------------------------------------------------------
void TFormBarbaImageMain::ExtractRed(const TImage * const source)
{
  TFormImage * const formNew = CreateFormImage();
  bikkel::ExtractRed(source,formNew->Image);
  formNew->ClientWidth  = formNew->Image->Picture->Bitmap->Width;
  formNew->ClientHeight = formNew->Image->Picture->Bitmap->Height;
  formNew->SetAllEnabled();
}
//---------------------------------------------------------------------------

