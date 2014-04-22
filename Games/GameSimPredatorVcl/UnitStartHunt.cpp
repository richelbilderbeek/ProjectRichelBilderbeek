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
#include <vcl.h>
#pragma hdrstop

#include "UnitStartHunt.h"
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include <algorithm>
#include <assert.hpp>
#include "UnitHunting.h"
#include "UnitChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormStartHunt *FormStartHunt;
//---------------------------------------------------------------------------
__fastcall TFormStartHunt::TFormStartHunt(TComponent* Owner)
  : TForm(Owner),
  mPreyWidth(48),
  mPreyHeight(48),
  mNprey(8),
  mPreyColor0(0x000000),
  mPreyColor1(0xFF0000),
  mPreyColor2(0x00FF00),
  mPreyColor3(0x0000FF),
  mPreyColor4(0xFFFF00),
  mPreyColor5(0x00FFFF),
  mPreyColor6(0xFF00FF),
  mPreyColor7(0xFFFFFF),
  mBackgroundColor0(0x080808),
  mBackgroundColor1(0xF80808),
  mBackgroundColor2(0x08F808),
  mBackgroundColor3(0x0808F8),
  mBackgroundColor4(0xF8F808),
  mBackgroundColor5(0x08F8F8),
  mBackgroundColor6(0xF808F8),
  mBackgroundColor7(0xF8F8F8),
  mHunt(0)
{
  ImageList1->Width  = mPreyWidth;
  ImageList1->Height = mPreyHeight;


  //Get a vector of images
  std::vector<TImage*> images(mNprey*2); //*2 as there are as many backgrounds
  images[ 0] = Image0;
  images[ 1] = Image1;
  images[ 2] = Image2;
  images[ 3] = Image3;
  images[ 4] = Image4;
  images[ 5] = Image5;
  images[ 6] = Image6;
  images[ 7] = Image7;
  images[ 8] = Image8;
  images[ 9] = Image9;
  images[10] = Image10;
  images[11] = Image11;
  images[12] = Image12;
  images[13] = Image13;
  images[14] = Image14;
  images[15] = Image15;

  //Resize the images
  for (int i=0; i<mNprey*2; ++i)
  {
    images[i]->Picture->Bitmap->Width  = mPreyWidth;
    images[i]->Picture->Bitmap->Height = mPreyHeight;
  }

  //Fill the images
  fillImage(Image0, mPreyColor0);
  fillImage(Image1, mPreyColor1);
  fillImage(Image2, mPreyColor2);
  fillImage(Image3, mPreyColor3);
  fillImage(Image4, mPreyColor4);
  fillImage(Image5, mPreyColor5);
  fillImage(Image6, mPreyColor6);
  fillImage(Image7, mPreyColor7);
  //Fill the background images
  fillImage(Image8 , mBackgroundColor0);
  fillImage(Image9 , mBackgroundColor1);
  fillImage(Image10, mBackgroundColor2);
  fillImage(Image11, mBackgroundColor3);
  fillImage(Image12, mBackgroundColor4);
  fillImage(Image13, mBackgroundColor5);
  fillImage(Image14, mBackgroundColor6);
  fillImage(Image15, mBackgroundColor7);

  ImageList1->AddMasked(Image0->Picture->Bitmap,clMoneyGreen);
  ImageList1->AddMasked(Image1->Picture->Bitmap,clMoneyGreen);
  ImageList1->AddMasked(Image2->Picture->Bitmap,clMoneyGreen);
  ImageList1->AddMasked(Image3->Picture->Bitmap,clMoneyGreen);
  ImageList1->AddMasked(Image4->Picture->Bitmap,clMoneyGreen);
  ImageList1->AddMasked(Image5->Picture->Bitmap,clMoneyGreen);
  ImageList1->AddMasked(Image6->Picture->Bitmap,clMoneyGreen);
  ImageList1->AddMasked(Image7->Picture->Bitmap,clMoneyGreen);
}
//---------------------------------------------------------------------------
void fillImage(TImage * image, const int& color)
{
  const char red = color%(256*256);
  const char green = color/(256)%256;
  const char blue = color/(256*256);

  //assert(image!=0);
  //assert(image->AutoSize==true);
  const int width = image->Width;
  const int height = image->Height;
  for (int y=0; y<height; ++y)
  {
    unsigned char * line=static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x<width; ++x)
    {
      line[x*3+0] = blue;  //Blue
      line[x*3+1] = green; //Green
      line[x*3+2] = red;   //Red
    }
  }
}
//---------------------------------------------------------------------------
void TFormStartHunt::setHunt(const int& hunt)
{
  Assert(hunt==1 || hunt==2);
  TextHunt->Caption = "Hunt #" + IntToStr(hunt);
  TextSubtitle->Caption = (hunt==1 ? "Practice hunting" : "Hunting on mutating prey");
  mHunt = hunt;
}
//---------------------------------------------------------------------------
void __fastcall TFormStartHunt::ImageBackgroundClick(TObject *Sender)
{
  int backgroundColor = 0;
  if (Sender == Image8 ) backgroundColor = mBackgroundColor0;
  if (Sender == Image9 ) backgroundColor = mBackgroundColor1;
  if (Sender == Image10) backgroundColor = mBackgroundColor2;
  if (Sender == Image11) backgroundColor = mBackgroundColor3;
  if (Sender == Image12) backgroundColor = mBackgroundColor4;
  if (Sender == Image13) backgroundColor = mBackgroundColor5;
  if (Sender == Image14) backgroundColor = mBackgroundColor6;
  if (Sender == Image15) backgroundColor = mBackgroundColor7;

  Assert(mHunt!=0);
  std::auto_ptr<TFormHunting> formHunt(new TFormHunting(
    this,
    backgroundColor,
    (mHunt==1 ? 0.0 : 0.1) ));
  formHunt->ShowModal();
  Close();
}
//---------------------------------------------------------------------------


void __fastcall TFormStartHunt::FormPaint(TObject *Sender)
{
  for (int i=0; i<mNprey; ++i)
  {
    FormChart->Chart1->Series[i]->Clear();
  }
  FormChart->Chart1->Series[0]->SeriesColor = static_cast<TColor>(mPreyColor0);
  FormChart->Chart1->Series[1]->SeriesColor = static_cast<TColor>(mPreyColor1);
  FormChart->Chart1->Series[2]->SeriesColor = static_cast<TColor>(mPreyColor2);
  FormChart->Chart1->Series[3]->SeriesColor = static_cast<TColor>(mPreyColor3);
  FormChart->Chart1->Series[4]->SeriesColor = static_cast<TColor>(mPreyColor4);
  FormChart->Chart1->Series[5]->SeriesColor = static_cast<TColor>(mPreyColor5);
  FormChart->Chart1->Series[6]->SeriesColor = static_cast<TColor>(mPreyColor6);
  FormChart->Chart1->Series[7]->SeriesColor = static_cast<TColor>(mPreyColor7);
        
}
//---------------------------------------------------------------------------

