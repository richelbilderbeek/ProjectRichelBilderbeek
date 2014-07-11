//---------------------------------------------------------------------------
/*
 *  BeerWanter 3. A simple game.
 *  Copyright (C) 2005  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
// This game can be downloaded at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitFormBeerWanter3H
#define UnitFormBeerWanter3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBeer;
        TImage *ImageBuffer;
        TImage *ImageBackGround;
        TApplicationEvents *ApplicationEvents1;
        void __fastcall ApplicationEvents1Idle(TObject *Sender,
          bool &Done);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
  int speed;
  int maxTop, maxLeft;
public:		// User declarations
  static const int mScreenWidth  = 600;
  static const int mScreenHeight = 400;
  static const String mCaptionBegin;
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
const String TFormMain::mCaptionBegin("BeerWanter 3. Copyright (C) 2005 Richel Bilderbeek. Beer already got: ");
//---------------------------------------------------------------------------
void EmptyBitmap(TImage * const pImage)
{
  const int maxy = pImage->Picture->Bitmap->Height;
  const int maxx = pImage->Picture->Bitmap->Width;
  for (int y=0; y!=maxy; ++y)
  {
    unsigned char * const pLine =
      static_cast<unsigned char *>(pImage->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=maxx; ++x)
    {
      pLine[x*3+0]= 0; //Blue
      pLine[x*3+1]= 0; //Green
      pLine[x*3+2]= 0; //Red
    }
  }
}
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
