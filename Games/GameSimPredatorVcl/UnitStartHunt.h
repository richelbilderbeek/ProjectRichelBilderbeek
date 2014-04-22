//---------------------------------------------------------------------------
/*
 *  SimPredator. A simple game to demonstrate selection and mutation
 *  Copyright (C) 2006  Richel Bilderbeek
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
// The program was developed from 19-05-2006 to 18-07-2006
// The program can be downloaded at http://www.richelbilderbeek.nl
// The author's e-mail adress can be found at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitStartHuntH
#define UnitStartHuntH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFormStartHunt : public TForm
{
__published:	// IDE-managed Components
        TStaticText *TextHunt;
        TRichEdit *RichEdit1;
        TImageList *ImageList1;
        TPanel *PanelPreyHolder;
        TPanel *PanelPrey;
        TImage *Image0;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        TImage *Image7;
        TRichEdit *RichEdit2;
        TPanel *PanelBackgroundHolder;
        TPanel *PanelBackground;
        TImage *Image8;
        TImage *Image9;
        TImage *Image10;
        TImage *Image11;
        TImage *Image12;
        TImage *Image13;
        TImage *Image14;
        TImage *Image15;
        TStaticText *TextSubtitle;
        void __fastcall ImageBackgroundClick(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
  int mHunt;
public:		// User declarations
  const int mPreyWidth;
  const int mPreyHeight;
  const int mNprey;
  const int mPreyColor0;
  const int mPreyColor1;
  const int mPreyColor2;
  const int mPreyColor3;
  const int mPreyColor4;
  const int mPreyColor5;
  const int mPreyColor6;
  const int mPreyColor7;
  const int mBackgroundColor0;
  const int mBackgroundColor1;
  const int mBackgroundColor2;
  const int mBackgroundColor3;
  const int mBackgroundColor4;
  const int mBackgroundColor5;
  const int mBackgroundColor6;
  const int mBackgroundColor7;
  void setHunt(const int& hunt);

        __fastcall TFormStartHunt(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStartHunt *FormStartHunt;
//---------------------------------------------------------------------------
void fillImage(TImage * image, const int& color);
//---------------------------------------------------------------------------

#endif
