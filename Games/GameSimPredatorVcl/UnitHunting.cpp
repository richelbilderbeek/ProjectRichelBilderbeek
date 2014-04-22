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

#include "UnitHunting.h"
//---------------------------------------------------------------------------
#include <Assert.hpp>
#include <mmsystem.hpp>
#include <math>
#include <boost/timer.hpp>
#include "UnitChart.h"
#include "UnitStartHunt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormHunting *FormHunting;
//---------------------------------------------------------------------------
__fastcall TFormHunting::TFormHunting(
    TComponent* Owner,
    const int& backgroundColor,
    const double& mutationRate)
  : TForm(Owner),
  mPrey(std::vector<Prey>(100)),
  #ifdef RICHEL_BILDERBEEK_IS_TESTING
    mHuntingTime(1),
  #else
    mHuntingTime(20), //Originally: 30
  #endif
  mPreyMax(100),
  mRound(0),
  mMutationRate(mutationRate)
{
  mClientWidth = Screen->Width;
  mClientHeight = Screen->Height;
  ImageBackground->Picture->Bitmap->Width  = mClientWidth;
  ImageBackground->Picture->Bitmap->Height = mClientHeight;
  ImageBuffer->Picture->Bitmap->Width  = mClientWidth;
  ImageBuffer->Picture->Bitmap->Height = mClientHeight;
  fillImage(ImageBackground, backgroundColor);

  for (int i=0; i<mPreyMax; ++i)
  {
    mPrey[i].mX = std::rand()%(mClientWidth - FormStartHunt->ImageList1->Width );
    mPrey[i].mY = std::rand()%(mClientHeight- FormStartHunt->ImageList1->Height);
    mPrey[i].mIndex = i%FormStartHunt->mNprey;
  }
  scorePrey();

  TimerStart->Enabled = true;
  TimerStart->OnTimer(0);

}
//---------------------------------------------------------------------------
void __fastcall TFormHunting::TimerStartTimer(TObject *Sender)
{
  ++TimerStart->Tag;
  Panel1->Visible = true;
  Panel1->Caption = "Only " + IntToStr(3 - TimerStart->Tag) + " second" + (3-TimerStart->Tag>1 ? "s" : "") +" before hunting...";
  if (TimerStart->Tag==3)
  {
    TimerStart->Tag = 0;
    TimerStart->Enabled = false;
    TimerGameDraw->Enabled = true;
    TimerGameTime->Enabled = true;
    Panel1->Visible = false;
    //rmChart->Visible = false;
    drawScreen();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormHunting::TimerGameDrawTimer(TObject *Sender)
{
  drawScreen();
}
//---------------------------------------------------------------------------
void __fastcall TFormHunting::TimerGameTimeTimer(TObject *Sender)
{
  ++TimerGameTime->Tag;
  //Caption = "SimPredator - Only " + IntToStr(mHuntingTime - TimerGameTime->Tag)
  //  + " seconds hunting left, " + IntToStr(mPrey.size()) + " prey left";
  if (TimerGameTime->Tag==mHuntingTime  || mPrey.size() < 25)
  {
    TimerGameTime->Tag=0;
    TimerGameDraw->Tag=0;
    TimerGameTime->Enabled = false;
    TimerGameDraw->Enabled = false;
    TimerReproduce->Enabled = false;
    TimerStart->Enabled = false;
    //Increment round
    ++mRound;
    if (mRound==5)
    {
      Panel1->Caption = "Finished hunting successfully!";
      Panel1->Refresh();
      //Sleep(3000); //DOES NOT WORK ANYMORE?!?!?
    }
    //Show prey chart
    scorePrey();
    FormChart->ShowModal();

    //while(FormChart->Visible==true)
    //{
    //  Application->ProcessMessages();
    //}
    //Finished?
    if (mRound==5) Close();

    TimerReproduce->Enabled = true;
    Panel1->Visible = true;
    Panel1->Caption = "Prey is reproducing...";
  }


}
//---------------------------------------------------------------------------
void __fastcall TFormHunting::TimerReproduceTimer(TObject *Sender)
{
  if (static_cast<int>(mPrey.size()) < mPreyMax)
  {
    const int i = std::rand() % mPrey.size();
    const int width  = FormStartHunt->ImageList1->Width;
    const int height = FormStartHunt->ImageList1->Height;
    const int nPrey = FormStartHunt->mNprey;

    Prey prey = mPrey[i];
    prey.mX += (std::rand()%(width+width))-width;
    prey.mY += (std::rand()%(height+height))-height;
    if (uniform() < mMutationRate)
    {
      prey.mIndex = std::rand()%nPrey;
    }

    mPrey.push_back(prey);
    drawScreen();
  }
  else
  {
    //Shuffle prey
    for (int i=0; i<mPreyMax; ++i)
    {
      mPrey[i].mX = std::rand() % (mClientWidth  - ImagePrey->Width );
      mPrey[i].mY = std::rand() % (mClientHeight - ImagePrey->Height);
    }
    /*
    //Increment round
    ++mRound;
    if (mRound==5)
    {
      Panel1->Caption = "Finished hunting successfully!";
      Panel1->Refresh();
      Sleep(3000);
    }
    //Show prey chart
    FormChart->Show();
    //Finished?
    if (mRound==5) Close();
    */
    //Continue
    TimerReproduce->Enabled = false;
    TimerStart->Enabled = true;


  }

}
//---------------------------------------------------------------------------
void TFormHunting::drawScreen()
{
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  const int nPrey = mPrey.size();
  for (int i=0; i<nPrey; ++i)
  {
    FormStartHunt->ImageList1->Draw(ImageBuffer->Canvas,mPrey[i].mX,mPrey[i].mY,mPrey[i].mIndex);
  }

  Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);

}
//---------------------------------------------------------------------------
void __fastcall TFormHunting::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  if (Panel1->Visible == true) return;

  static std::vector<Prey>::iterator iter;
  const int nPrey = mPrey.size();
  if (nPrey < FormStartHunt->mNprey) return;
  for (int i=nPrey-1; i>-1; --i)
  {
    if (
         X > mPrey[i].mX
      && Y > mPrey[i].mY
      && X < mPrey[i].mX + FormStartHunt->ImageList1->Width
      && Y < mPrey[i].mY + FormStartHunt->ImageList1->Height
      )
    { //Prey found!
      iter = &mPrey[i];
      // = find(myVector.begin(),myVector.end(),myElement);
      //if (i==myVector.end()) break;
      mPrey.erase(iter);

      //mPrey[i] = mPrey.back();
      //mPrey.pop_back();
      drawScreen();
      return;
    }
  }
  drawScreen();
}
//---------------------------------------------------------------------------
void TFormHunting::scorePrey()
{
  const int nPrey = FormStartHunt->mNprey;
  const int maxPreyIndex = this->mPrey.size();
  std::vector<int> histo(nPrey,0);
  for (int i=0; i<maxPreyIndex; ++i)
  {
    ++histo[ mPrey[i].mIndex ];
  }
  for (int i=0; i<nPrey; ++i)
  {
    FormChart->Chart1->Series[i]->AddY(histo[i]);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFormHunting::FormCreate(TObject *Sender)
{
  const TCursor myCursor = static_cast<TCursor>(22);
  Screen->Cursors[myCursor] = LoadCursorFromFile("CursorSkull.cur");
  Cursor = myCursor;
  Screen->Cursor = myCursor;
  this->Cursor = myCursor;
  Panel1->Cursor = myCursor;
  FormChart->Chart1->Cursor = myCursor;
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
double uniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------

