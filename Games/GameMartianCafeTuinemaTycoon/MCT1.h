//---------------------------------------------------------------------------
/*
  Martian Cafe Tuinema Tycoon, bartender game
  Copyright (C) 2005  Joost van den Bogaart

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
#ifndef MCT1H
#define MCT1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *BackgroundImage;
        TImage *L0Image;
        TImage *R0Image;
        TTimer *Bewegingstimer;
        TImage *ImageCanvas;
        TImage *L1Image;
        TImage *L2Image;
        TImage *R1Image;
        TImage *R2Image;
        TImage *ArrowImage;
        TImage *ItemImage;
        TImage *StaffImage;
        TImage *GlasImage;
        TImage *DienbladImage;
        TImage *OrkestImage1;
        TImage *OrkestImage2;
        TImage *WallImage;
        TPanel *Panel1;
        TLabel *DrinkLabel;
        TLabel *DrinkLabel2;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *Panel2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BewegingstimerTimer(TObject *Sender);
        void __fastcall ArrowImageClick(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
