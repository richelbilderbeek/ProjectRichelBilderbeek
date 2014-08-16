/*
  Boenken 2, a simple game
  Copyright (C) 2007  Richel Bilderbeek

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

#include <memory>
#include <vector>
#include <cassert>
#include "UnitPlayer.h"
//---------------------------------------------------------------------------
#include "UnitFormBoenken2Menu.h"
#include "UnitFormBoenken2PressKey.h"
#include "UnitFormBoenken2Game.h"
#include "UnitFormBoenken2About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBoenken2Menu *FormBoenken2Menu;
//---------------------------------------------------------------------------
__fastcall TFormBoenken2Menu::TFormBoenken2Menu(TComponent* Owner)
  : TForm(Owner),
    mGraphics(graphicsNewSchool),
    mControls(control2keys)
{
  ImageNunitsMinus->Picture->Bitmap->Height = ImageNunitsMinus->Height;
  ImageNunitsMinus->Picture->Bitmap->Width  = ImageNunitsMinus->Width;
  ImageNunitsPlus->Picture->Bitmap->Height = ImageNunitsPlus->Height;
  ImageNunitsPlus->Picture->Bitmap->Width  = ImageNunitsPlus->Width;

  ImageNredMinus->Picture->Bitmap->Height = ImageNredMinus->Height;
  ImageNredMinus->Picture->Bitmap->Width  = ImageNredMinus->Width;
  ImageNredPlus->Picture->Bitmap->Height = ImageNredPlus->Height;
  ImageNredPlus->Picture->Bitmap->Width  = ImageNredPlus->Width;

  ImageNblueMinus->Picture->Bitmap->Height = ImageNblueMinus->Height;
  ImageNblueMinus->Picture->Bitmap->Width  = ImageNblueMinus->Width;
  ImageNbluePlus->Picture->Bitmap->Height = ImageNbluePlus->Height;
  ImageNbluePlus->Picture->Bitmap->Width  = ImageNbluePlus->Width;

  ImageGraphicsOldSchool->Picture->Bitmap->Height = ImageGraphicsOldSchool->Height;
  ImageGraphicsOldSchool->Picture->Bitmap->Width  = ImageGraphicsOldSchool->Width;
  ImageGraphicsNewSchool->Picture->Bitmap->Height = ImageGraphicsNewSchool->Height;
  ImageGraphicsNewSchool->Picture->Bitmap->Width  = ImageGraphicsNewSchool->Width;
  ImageGraphicsChosen->Picture->Bitmap->Height = ImageGraphicsChosen->Height;
  ImageGraphicsChosen->Picture->Bitmap->Width  = ImageGraphicsChosen->Width;

  DrawGlobeMinus(ImageNunitsMinus,255,255,255);
  DrawGlobePlus( ImageNunitsPlus ,255,255,255);
  DrawGlobeMinus(ImageNredMinus  ,255,  0,  0);
  DrawGlobePlus( ImageNredPlus   ,255,  0,  0);
  DrawGlobeMinus(ImageNblueMinus ,  0,  0,255);
  DrawGlobePlus( ImageNbluePlus  ,  0,  0,255);

  DrawCircle( ImageGraphicsOldSchool,   0,255,  0);
  DrawGlobe ( ImageGraphicsNewSchool,   0,255,  0);
  //Default: New School graphics
  ImageGraphicsChosen->Picture->Graphic = ImageGraphicsNewSchool->Picture->Graphic;

  TrackBarFriction->OnChange(0);
  //ImageNunits->Canvas->Font->Size = ImageNunits->Picture->Graphic->Height;
  //ImageNunits->Canvas->TextOutA(0,0,"+");
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ButtonStartClick(TObject *Sender)
{
  //Distribute the players over the units
  const int nUnits = PanelNunits->Caption.ToInt();
  std::vector<Player> players(nUnits);
  const std::vector<Player>::iterator playerEnd = players.end();
  const std::vector<Player>::iterator redEnd = mPlayerRedKeys.end();
  const std::vector<Player>::iterator blueEnd = mPlayerBlueKeys.end();
  std::vector<Player>::iterator red = mPlayerRedKeys.begin();
  std::vector<Player>::iterator blue = mPlayerBlueKeys.begin();
  for (
    std::vector<Player>::iterator player = players.begin();
    player!=playerEnd;
    ++player)
  {
    if (red == redEnd) red = mPlayerRedKeys.begin();
    (*player).keyAccel     = (*red).keyAccel;
    (*player).keyBrake     = (*red).keyBrake;
    (*player).keyTurnLeft  = (*red).keyTurnLeft;
    (*player).keyTurnRight = (*red).keyTurnRight;
    ++red;

    ++player;
    if (player==playerEnd) break;

    if (blue == blueEnd) blue = mPlayerBlueKeys.begin();
    (*player).keyAccel     = (*blue).keyAccel;
    (*player).keyBrake     = (*blue).keyBrake;
    (*player).keyTurnLeft  = (*blue).keyTurnLeft;
    (*player).keyTurnRight = (*blue).keyTurnRight;
    ++blue;
  }

  std::auto_ptr<TFormBoenken2Game> f(
    new TFormBoenken2Game(0,players,mGraphics,mControls,mFriction));
  f->ShowModal();

}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ButtonCalibrateClick(TObject *Sender)
{
  const int nUnits = PanelNunits->Caption.ToInt();
  const int nRed   = PanelNred->Caption.ToInt();
  const int nBlue  = PanelNblue->Caption.ToInt();
  assert(nUnits >= nRed + nBlue);

  mPlayerRedKeys.resize(nRed);
  for (int i=0; i!=nRed; ++i)
  {
    {
      const String message = "Red player #" + IntToStr(i+1) + ", please press key for 'Accelerate'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerRedKeys[i].keyAccel = f->ModalResult;
    }
    if (mControls==control4keys)
    {
      const String message = "Red player #" + IntToStr(i+1) + ", please press key for 'Brake'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerRedKeys[i].keyBrake = f->ModalResult;
    }
    else
    {
      mPlayerRedKeys[i].keyBrake = 0;
    }

    if (mControls==control4keys)
    {
      const String message = "Red player #" + IntToStr(i+1) + ", please press key for 'Turn left'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerRedKeys[i].keyTurnLeft = f->ModalResult;
    }
    else
    {
      mPlayerRedKeys[i].keyTurnLeft = 0;
    }

    {
      const String message = "Red player #" + IntToStr(i+1) + ", please press key for 'Turn right'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerRedKeys[i].keyTurnRight = f->ModalResult;
    }
  }

  mPlayerBlueKeys.resize(nBlue);
  for (int i=0; i!=nBlue; ++i)
  {
    {
      const String message = "Blue player #" + IntToStr(i+1) + ", please press key for 'Accelerate'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerBlueKeys[i].keyAccel = f->ModalResult;
    }
    if (mControls==control4keys)
    {
      const String message = "Blue player #" + IntToStr(i+1) + ", please press key for 'Brake'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerBlueKeys[i].keyBrake = f->ModalResult;
    }
    else
    {
      mPlayerBlueKeys[i].keyBrake = 0;
    }

    if (mControls==control4keys)
    {
      const String message = "Blue player #" + IntToStr(i+1) + ", please press key for 'Turn left'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerBlueKeys[i].keyTurnLeft = f->ModalResult;
    }
    else
    {
      mPlayerBlueKeys[i].keyTurnLeft = 0;
    }

    {
      const String message = "Blue player #" + IntToStr(i+1) + ", please press key for 'Turn right'.";
      std::auto_ptr<TFormBoenken2PressKey> f(new TFormBoenken2PressKey(0,message));
      f->ShowModal();
      mPlayerBlueKeys[i].keyTurnRight = f->ModalResult;
    }
  }


  ButtonStart->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ButtonAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormBoenken2About> f(new TFormBoenken2About(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void DrawGlobeMinus(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  DrawGlobe(image,red,green,blue);
  const int height = image->Picture->Bitmap->Height;
  const int width  = image->Picture->Bitmap->Width;
  image->Canvas->Pen->Width = height / 10;
  image->Canvas->Pen->Color = static_cast<TColor>(RGB(red,green,blue));
  image->Canvas->MoveTo(1 * width / 4,height / 2);
  image->Canvas->LineTo(3 * width / 4,height / 2);
}
//---------------------------------------------------------------------------
void DrawGlobePlus(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  DrawGlobe(image,red,green,blue);
  const int height = image->Picture->Bitmap->Height;
  const int width  = image->Picture->Bitmap->Width;
  image->Canvas->Pen->Width = height / 10;
  image->Canvas->Pen->Color = static_cast<TColor>(RGB(red,green,blue));
  image->Canvas->MoveTo(1 * width / 4,height / 2);
  image->Canvas->LineTo(3 * width / 4,height / 2);
  image->Canvas->MoveTo(width / 2,1 * height / 4);
  image->Canvas->LineTo(width / 2,3 * height / 4);
}
//---------------------------------------------------------------------------

void __fastcall TFormBoenken2Menu::ImageNunitsMinusClick(TObject *Sender)
{
  const int nUnits = PanelNunits->Caption.ToInt();
  if (nUnits == 2) return;
  const int nRed   = PanelNred->Caption.ToInt();
  const int nBlue  = PanelNblue->Caption.ToInt();
  if (nUnits == nRed + nBlue) return;
  PanelNunits->Caption = nUnits - 1;
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ImageNunitsPlusClick(TObject *Sender)
{
  const int nUnits = PanelNunits->Caption.ToInt();
  if (nUnits == 20) return;
  PanelNunits->Caption = nUnits + 1;
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ImageNredMinusClick(TObject *Sender)
{
  const int nRed = PanelNred->Caption.ToInt();
  if (nRed == 1) return;
  PanelNred->Caption = nRed - 1;
  ButtonStart->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ImageNredPlusClick(TObject *Sender)
{
  const int nRed   = PanelNred->Caption.ToInt();
  const int nUnits = PanelNunits->Caption.ToInt();
  const int nBlue  = PanelNblue->Caption.ToInt();
  if (nBlue + nRed == 20) return;
  PanelNred->Caption = nRed + 1;
  if (nUnits < nRed + nBlue + 1 && nUnits < 20)
  {
    PanelNunits->Caption = nUnits + 1;
  }
  ButtonStart->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ImageNblueMinusClick(TObject *Sender)
{
  const int nBlue = PanelNblue->Caption.ToInt();
  if (nBlue == 1) return;
  PanelNblue->Caption = nBlue - 1;
  ButtonStart->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ImageNbluePlusClick(TObject *Sender)
{
  const int nBlue  = PanelNblue->Caption.ToInt();
  const int nUnits = PanelNunits->Caption.ToInt();
  const int nRed   = PanelNred->Caption.ToInt();
  if (nBlue + nRed == 20) return;
  PanelNblue->Caption = nBlue + 1;
  if (nUnits < nRed + nBlue + 1 && nUnits < 20)
  {
    PanelNunits->Caption = nUnits + 1;
  }
  ButtonStart->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Menu::ImageGraphicsOldSchoolClick(
      TObject *Sender)
{
  mGraphics = graphicsOldSchool;
  ImageGraphicsChosen->Picture->Graphic = ImageGraphicsOldSchool->Picture->Graphic;
}
//---------------------------------------------------------------------------

void __fastcall TFormBoenken2Menu::ImageGraphicsNewSchoolClick(
      TObject *Sender)
{
  mGraphics = graphicsNewSchool;
  ImageGraphicsChosen->Picture->Graphic = ImageGraphicsNewSchool->Picture->Graphic;
}
//---------------------------------------------------------------------------

void __fastcall TFormBoenken2Menu::ImageControlsTwoClick(TObject *Sender)
{
  if (mControls!=control2keys)
  {
    mControls = control2keys;
    ImageControlsChosen->Picture->Graphic = ImageControlsTwo->Picture->Graphic;
    ButtonStart->Enabled = false;
    ButtonCalibrate->Enabled = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormBoenken2Menu::ImageControlsFourClick(TObject *Sender)
{
  if (mControls!=control4keys)
  {
    mControls = control4keys;
    ImageControlsChosen->Picture->Graphic = ImageControlsFour->Picture->Graphic;
    ButtonStart->Enabled = false;
    ButtonCalibrate->Enabled = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormBoenken2Menu::TrackBarFrictionChange(TObject *Sender)
{
  const double fraction
    = static_cast<double>(TrackBarFriction->Position)
    / static_cast<double>(TrackBarFriction->Max);
  mFriction = 1.0 - (fraction * 0.01);
  if (mFriction == 1.0) PanelFrictionValue->Caption = "None";
  else if (mFriction > 0.9966) PanelFrictionValue->Caption = "Low";
  else if (mFriction > 0.9933) PanelFrictionValue->Caption = "Mid";
  else PanelFrictionValue->Caption = "High";
}
//---------------------------------------------------------------------------

