//---------------------------------------------------------------------------
/*
  Super Tron, a simple game
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
#include <vcl.h>
#pragma hdrstop

#include <cassert>
#include <boost/scoped_ptr.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include "UnitGraphics.h"
#include "UnitFormSuperTronMenu.h"
#include "UnitFormPressKey.h"
#include "UnitFormSelectColor.h"
#include "UnitFormSuperTronGame.h"
#include "UnitFormSuperTronAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSuperTronMenu *FormSuperTronMenu;
//---------------------------------------------------------------------------
__fastcall TFormSuperTronMenu::TFormSuperTronMenu(TComponent* Owner)
  : TForm(Owner),
    mDonutShapedWorld(true),
    mCanWalkThroughOwnColor(false)
{
  ImageNplayersMinus->Picture->Graphic->Width  = 80;
  ImageNplayersMinus->Picture->Graphic->Height = 80;
  ImageNplayersPlus->Picture->Graphic->Width   = 80;
  ImageNplayersPlus->Picture->Graphic->Height  = 80;
  DrawGlobeMinus(ImageNplayersMinus,255,196,196);
  DrawGlobePlus(ImageNplayersPlus,196,196,255);

  TrackBarSpeed->OnChange(0);
  TrackBarWidth->OnChange(0);
  TrackBarHeight->OnChange(0);
  TrackBarNangles->OnChange(0);
}
//---------------------------------------------------------------------------

void __fastcall TFormSuperTronMenu::ButtonCalibrateClick(TObject *Sender)
{
  const int nPlayers = PanelNplayers->Caption.ToIntDef(-1);
  assert(nPlayers!=-1);
  mPlayers.resize(nPlayers);
  for (int i=0; i!=nPlayers; ++i)
  {
    //Key left
    {
      const String message = "Player #" + IntToStr(i+1) + ", please press key for 'Turn left'.";
      std::auto_ptr<TFormPressKey> f(new TFormPressKey(0,message));
      f->ShowModal();
      mPlayers[i].keyLeft = f->ModalResult;
    }
    //Key right
    {
      const String message = "Player #" + IntToStr(i+1) + ", please press key for 'Turn right'.";
      std::auto_ptr<TFormPressKey> f(new TFormPressKey(0,message));
      f->ShowModal();
      mPlayers[i].keyRight = f->ModalResult;
    }
    //Color
    //Choose color
    {
      std::auto_ptr<TFormSelectColor> f(new TFormSelectColor(0));
      f->ShowModal();
      const int colorIndex = f->ModalResult - 10;
      assert(colorIndex >= 0 && colorIndex < 20);
      const double fraction = static_cast<double>(colorIndex) / 20.0;
      unsigned char r,g,b;
      Rainbow(fraction,r,g,b);
      mPlayers[i].color = RgbToColor(r,g,b);
    }
  }
  ButtonStart->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSuperTronMenu::ButtonStartClick(TObject *Sender)
{
  const double fractionSpeed
  = static_cast<double>(TrackBarSpeed->Position)
  / static_cast<double>(TrackBarSpeed->Max);
  const double fractionWidth
  = static_cast<double>(TrackBarWidth->Position)
  / static_cast<double>(TrackBarWidth->Max);
  const double fractionHeight
  = static_cast<double>(TrackBarHeight->Position)
  / static_cast<double>(TrackBarHeight->Max);

  const int speed = 1000.0 - (fractionSpeed * 999.0);
  assert(speed > 0);
  const int maxx = 100.0 + (fractionWidth * static_cast<double>(Monitor->Width - 200));
  const int maxy = 100.0 + (fractionHeight * static_cast<double>(Monitor->Height - 200));
  boost::scoped_ptr<TFormSuperTronGame> f(
    new TFormSuperTronGame(
      0,
      mPlayers,
      speed,
      maxx,
      maxy,
      mDonutShapedWorld,
      mCanWalkThroughOwnColor
      ));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormSuperTronMenu::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  switch(Key)
  {
    case VK_ADD:
      ImageNplayersPlus->OnClick(0);
      break;
    case VK_SUBTRACT:
      ImageNplayersMinus->OnClick(0);
      break;
    case 83: // 's'
      if (mDonutShapedWorld == true)
      {
        ImageWorldFlat->OnClick(0);
      }
      else
      {
        ImageWorldDonut->OnClick(0);
      }
      break;
    case 72: // 'h'
      if (mCanWalkThroughOwnColor == true)
      {
        ImageCannotWalkThroughOwnColor->OnClick(0);
      }
      else
      {
        ImageCanWalkThroughOwnColor->OnClick(0);
      }
      break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSuperTronMenu::ImageNplayersMinusClick(
      TObject *Sender)
{
  const int nPlayers = PanelNplayers->Caption.ToIntDef(-1);
  assert(nPlayers!=-1);
  if (nPlayers > 2)
  {
    PanelNplayers->Caption = IntToStr(nPlayers - 1);
    ButtonStart->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSuperTronMenu::ImageNplayersPlusClick(
      TObject *Sender)
{
  const int nPlayers = PanelNplayers->Caption.ToIntDef(-1);
  assert(nPlayers!=-1);
  if (nPlayers < 20)
  {
    PanelNplayers->Caption = IntToStr(nPlayers + 1);
    ButtonStart->Enabled = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormSuperTronMenu::TrackBarSpeedChange(TObject *Sender)
{
  const double fraction
  = static_cast<double>(TrackBarSpeed->Position)
  / static_cast<double>(TrackBarSpeed->Max);
  if (fraction < 0.1) PanelSpeedValue->Caption = "Slowest";
  else if (fraction < 0.40) PanelSpeedValue->Caption = "Slow";
  else if (fraction < 0.60) PanelSpeedValue->Caption = "Normal";
  else if (fraction < 0.90) PanelSpeedValue->Caption = "Fast";
  else PanelSpeedValue->Caption = "Fastest";
}
//---------------------------------------------------------------------------

void __fastcall TFormSuperTronMenu::TrackBarWidthChange(TObject *Sender)
{
  const double fraction
  = static_cast<double>(TrackBarWidth->Position)
  / static_cast<double>(TrackBarWidth->Max);
  if (fraction < 0.1) PanelWidthValue->Caption = "Smallest";
  else if (fraction < 0.40) PanelWidthValue->Caption = "Small";
  else if (fraction < 0.60) PanelWidthValue->Caption = "Medium";
  else if (fraction < 0.90) PanelWidthValue->Caption = "Large";
  else PanelWidthValue->Caption = "Largest";
}
//---------------------------------------------------------------------------

void __fastcall TFormSuperTronMenu::TrackBarHeightChange(TObject *Sender)
{
  const double fraction
  = static_cast<double>(TrackBarHeight->Position)
  / static_cast<double>(TrackBarHeight->Max);
  if (fraction < 0.1) PanelHeightValue->Caption = "Smallest";
  else if (fraction < 0.40) PanelHeightValue->Caption = "Small";
  else if (fraction < 0.60) PanelHeightValue->Caption = "Medium";
  else if (fraction < 0.90) PanelHeightValue->Caption = "Large";
  else PanelHeightValue->Caption = "Largest";
}
//---------------------------------------------------------------------------

void __fastcall TFormSuperTronMenu::ImageWorldFlatClick(TObject *Sender)
{
  ImageWorldChosen->Picture->Graphic = ImageWorldFlat->Picture->Graphic;
  mDonutShapedWorld = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormSuperTronMenu::ImageWorldDonutClick(TObject *Sender)
{
  ImageWorldChosen->Picture->Graphic = ImageWorldDonut->Picture->Graphic;
  mDonutShapedWorld = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSuperTronMenu::ImageCanWalkThroughOwnColorClick(
      TObject *Sender)
{
  ImageCanWalkThroughOwnColorChosen->Picture->Graphic
  = ImageCanWalkThroughOwnColor->Picture->Graphic;
  mCanWalkThroughOwnColor = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormSuperTronMenu::ImageCannotWalkThroughOwnColorClick(
      TObject *Sender)
{
  ImageCanWalkThroughOwnColorChosen->Picture->Graphic
  = ImageCannotWalkThroughOwnColor->Picture->Graphic;
  mCanWalkThroughOwnColor = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSuperTronMenu::ButtonAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormSuperTronAbout> f(new TFormSuperTronAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormSuperTronMenu::TrackBarNanglesChange(TObject *Sender)
{
  const int nAngles = TrackBarNangles->Position;
  PanelNanglesValue->Caption = nAngles;
  SuperTronPlayer::deltaAngle = (2.0 * M_PI) / static_cast<double>(nAngles);
}
//---------------------------------------------------------------------------

