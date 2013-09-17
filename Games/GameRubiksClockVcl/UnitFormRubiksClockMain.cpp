//---------------------------------------------------------------------------
/*
  Rubik's Clock Simulator. Simulates Rubik's Clock.
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
#include <cmath>
#include <cassert>
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormRubiksClockMain.h"
#include "UnitFormRubiksClockAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRubiksClockMain *FormRubiksClockMain;
//---------------------------------------------------------------------------
__fastcall TFormRubiksClockMain::TFormRubiksClockMain(TComponent* Owner)
        : TForm(Owner)
{
  OnResize(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormRubiksClockMain::FormResize(TObject *Sender)
{
  ImageClockFront->Picture->Bitmap->Width  = ClientWidth / 2;
  ImageClockFront->Picture->Bitmap->Height = ClientHeight - Panel1->Height;
  ImageClockBack->Left = ImageClockFront->Picture->Bitmap->Width;
  ImageClockBack->Picture->Bitmap->Width  = ClientWidth - ImageClockFront->Picture->Bitmap->Width;
  ImageClockBack->Picture->Bitmap->Height = ClientHeight - Panel1->Height;
  DrawScreen();
}
//---------------------------------------------------------------------------
void TFormRubiksClockMain::DrawScreen()
{
  ImageClockFront->Visible = false;
  ImageClockBack->Visible = false;
  DrawRubiksClock(
    mClock.GetFrontTimes(),
    mClock.GetFrontPegs(),
    static_cast<TColor>(RGB(255,96,96)),
    static_cast<TColor>(RGB(255,64,64)),
    ImageClockFront);
  DrawRubiksClock(
    mClock.GetBackTimes(),
    mClock.GetBackPegs(),
    static_cast<TColor>(RGB(96,96,255)),
    static_cast<TColor>(RGB(64,64,255)),
    ImageClockBack);
  ImageClockFront->Visible = true;
  ImageClockBack->Visible = true;
}
//---------------------------------------------------------------------------
void DrawRubiksClock(
  const RubiksClockTimes& times,
  const RubiksClockPegs& pegs,
  const TColor colorCasing,
  const TColor colorClock,
  TImage * const image)
{

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  PaintVcl(image,0,0,0);

  //Draw main clock ring
  image->Canvas->Pen->Color = clBlack;
  image->Canvas->Brush->Color = colorCasing;
  image->Canvas->Ellipse(0,0,maxx,maxy);

  //Draw the clocks and pegs
  {
    const double dX = static_cast<double>(maxx) / 3.0;
    const double dY = static_cast<double>(maxy) / 3.0;
    const double dXtenth = 0.1 * dX;
    const double dYtenth = 0.1 * dY;
    for (int y=0; y!=3; ++y)
    {
      for (int x=0; x!=3; ++x)
      {
        //Draw outer ring
        image->Canvas->Pen->Width = 1;
        image->Canvas->Brush->Color = colorCasing;
        image->Canvas->Pen->Color = colorClock;
        image->Canvas->Ellipse(
          static_cast<double>(x+0) * dX,
          static_cast<double>(y+0) * dY,
          static_cast<double>(x+1) * dX,
          static_cast<double>(y+1) * dY);
        //Draw clock ring
        image->Canvas->Brush->Color = colorClock;
        image->Canvas->Ellipse(
          static_cast<double>(x+0) * dX + dXtenth,
          static_cast<double>(y+0) * dY + dYtenth,
          static_cast<double>(x+1) * dX - dXtenth,
          static_cast<double>(y+1) * dY - dYtenth);
        //Draw time
        image->Canvas->Pen->Color = clBlack;
        image->Canvas->Pen->Width = 5;
        const double angle = (2.0 * M_PI)
          *(static_cast<double>(times.times[x][y]) / 12.0);
        image->Canvas->MoveTo(
          (static_cast<double>(x)+0.5) * dX,
          (static_cast<double>(y)+0.5) * dY );
        image->Canvas->LineTo(
          ( (static_cast<double>(x)+0.5) * dX) + (std::sin(angle) * ((0.5 * dX) - dXtenth) ),
          ( (static_cast<double>(y)+0.5) * dY) - (std::cos(angle) * ((0.5 * dY) - dYtenth) ) );
      }
    }
    image->Canvas->Pen->Width = 3;
    //Draw the pegs
    for (int y=0; y!=2; ++y)
    {
      for (int x=0; x!=2; ++x)
      {
        image->Canvas->Pen->Color = clBlack;
        image->Canvas->Brush->Color = clYellow;
        const int delta = (pegs.pegs[x][y] == false ? 10 : 1);
        for (int i=0; i!=delta; ++i)
        {
          image->Canvas->Ellipse(
            ( i + ((static_cast<double>(x)+1.0) * dX) + dXtenth),
            ( i + ((static_cast<double>(y)+1.0) * dY) + dYtenth),
            ( i + ((static_cast<double>(x)+1.0) * dX) - dXtenth),
            ( i + ((static_cast<double>(y)+1.0) * dY) - dYtenth) );

        }
      }
    }
  }

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      myLine[x*3+2] = red  ; //Red
      myLine[x*3+1] = green; //Green
      myLine[x*3+0] = blue ; //Blue
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormRubiksClockMain::ImageClockFrontMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  const int maxx = ImageClockFront->Picture->Bitmap->Width;
  const int maxy = ImageClockFront->Picture->Bitmap->Height;
  if ( X < maxx / 6 && Y < maxy / 6)
  {
    if (Button == mbLeft)
    {
      mClock.TurnWheel(topLeft,1);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(topLeft,11);
    }
  }
  else if ( X > 5 * (maxx / 6) && Y < maxy / 6)
  {
    if (Button == mbLeft)
    {
      mClock.TurnWheel(topRight,1);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(topRight,11);
    }
  }
  else if ( X < maxx / 6 && Y > 5 * (maxy / 6) )
  {
    //Wheel bottom left 
    if (Button == mbLeft)
    {
      mClock.TurnWheel(bottomLeft,1);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(bottomLeft,11);
    }
  }
  else if ( X > 5 * (maxx / 6) && Y > 5 * (maxy / 6) )
  {
    //Wheel bottom right
    if (Button == mbLeft)
    {
      mClock.TurnWheel(bottomRight,1);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(bottomRight,11);
    }
  }
  else if ( X > (maxx / 3) - (maxx / 10)
    && X < (maxx / 3) + (maxx / 10)
    && Y > (maxy / 3) - (maxy / 10)
    && Y < (maxy / 3) + (maxy / 10) )
  {
    mClock.ChangePeg(topLeft, !mClock.GetFrontPegs().pegs[0][0]);
  }
  else if ( X > (2 *(maxx / 3)) - (maxx / 10)
    && X < (2 * (maxx / 3)) + (maxx / 10)
    && Y > (maxy / 3) - (maxy / 10)
    && Y < (maxy / 3) + (maxy / 10) )
  {
    mClock.ChangePeg(topRight, !mClock.GetFrontPegs().pegs[1][0]);
  }
  else if ( X > (maxx / 3) - (maxx / 10)
    && X < (maxx / 3) + (maxx / 10)
    && Y > (2 * (maxy / 3)) - (maxy / 10)
    && Y < (2 * (maxy / 3)) + (maxy / 10) )
  {
    mClock.ChangePeg(bottomLeft, !mClock.GetFrontPegs().pegs[0][1]);
  }
  else if ( X > (2 * (maxx / 3)) - (maxx / 10)
    && X < (2 * (maxx / 3)) + (maxx / 10)
    && Y > (2 * (maxy / 3)) - (maxy / 10)
    && Y < (2 * (maxy / 3)) + (maxy / 10) )
  {
    mClock.ChangePeg(bottomRight, !mClock.GetFrontPegs().pegs[1][1]);
  }

  DrawScreen();

}
//---------------------------------------------------------------------------
void __fastcall TFormRubiksClockMain::ImageClockBackMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  const int maxx = ImageClockFront->Picture->Bitmap->Width;
  const int maxy = ImageClockFront->Picture->Bitmap->Height;
  if ( X < maxx / 6 && Y < maxy / 6)
  {
    if (Button == mbLeft)
    {
      mClock.TurnWheel(topRight,11);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(topRight,1);
    }
  }
  else if ( X > 5 * (maxx / 6) && Y < maxy / 6)
  {
    if (Button == mbLeft)
    {
      mClock.TurnWheel(topLeft,11);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(topLeft,1);
    }
  }
  else if ( X < maxx / 6 && Y > 5 * (maxy / 6) )
  {
    //Wheel bottom left
    if (Button == mbLeft)
    {
      mClock.TurnWheel(bottomRight,11);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(bottomRight,1);
    }
  }
  else if ( X > 5 * (maxx / 6) && Y > 5 * (maxy / 6) )
  {
    //Wheel bottom right
    if (Button == mbLeft)
    {
      mClock.TurnWheel(bottomLeft,11);
    }
    else if (Button == mbRight)
    {
      mClock.TurnWheel(bottomLeft,1);
    }
  }
  else if ( X > (maxx / 3) - (maxx / 10)
    && X < (maxx / 3) + (maxx / 10)
    && Y > (maxy / 3) - (maxy / 10)
    && Y < (maxy / 3) + (maxy / 10) )
  {
    mClock.ChangePeg(topRight, !mClock.GetFrontPegs().pegs[1][0]);
  }
  else if ( X > (2 *(maxx / 3)) - (maxx / 10)
    && X < (2 * (maxx / 3)) + (maxx / 10)
    && Y > (maxy / 3) - (maxy / 10)
    && Y < (maxy / 3) + (maxy / 10) )
  {
    mClock.ChangePeg(topLeft, !mClock.GetFrontPegs().pegs[0][0]);
  }
  else if ( X > (maxx / 3) - (maxx / 10)
    && X < (maxx / 3) + (maxx / 10)
    && Y > (2 * (maxy / 3)) - (maxy / 10)
    && Y < (2 * (maxy / 3)) + (maxy / 10) )
  {
    mClock.ChangePeg(bottomRight, !mClock.GetFrontPegs().pegs[1][1]);
  }
  else if ( X > (2 * (maxx / 3)) - (maxx / 10)
    && X < (2 * (maxx / 3)) + (maxx / 10)
    && Y > (2 * (maxy / 3)) - (maxy / 10)
    && Y < (2 * (maxy / 3)) + (maxy / 10) )
  {
    mClock.ChangePeg(bottomLeft, !mClock.GetFrontPegs().pegs[0][1]);
  }

  DrawScreen();
}
//---------------------------------------------------------------------------


void __fastcall TFormRubiksClockMain::ButtonAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormRubiksClockAbout> f(new TFormRubiksClockAbout(0));
  f->ShowModal();        
}
//---------------------------------------------------------------------------
void __fastcall TFormRubiksClockMain::ButtonShuffleClick(TObject *Sender)
{
  for (int i=0; i!=10000; ++i)
  {
    //Set a random peg
    mClock.ChangePeg(
      static_cast<RubiksClockSide>(std::rand() >> 4% 4),
      ((std::rand() >> 4) % 2 == 0 ? true : false) );
    //Turn a random wheel
    mClock.TurnWheel(
      static_cast<RubiksClockSide>(std::rand() >> 4 % 4),
      std::rand() % 12);
  }
  DrawScreen();
}
//---------------------------------------------------------------------------

