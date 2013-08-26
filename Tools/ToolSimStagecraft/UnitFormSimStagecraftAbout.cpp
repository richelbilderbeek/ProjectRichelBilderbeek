//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <cassert>
#include <cmath>
#include <boost/shared_ptr.hpp>
#include "UnitFormSimStagecraftAbout.h"
#include "UnitFormSimStagecraftWhatsNew.h"
#include "UnitFormSimStagecraftOtherLicences.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimStagecraftAbout *FormSimStagecraftAbout;
//---------------------------------------------------------------------------
__fastcall TFormSimStagecraftAbout::TFormSimStagecraftAbout(TComponent* Owner)
  : TForm(Owner), mDr(1), mDg(1), mDb(1)
{
  DrawBackground();
  TimerMain->OnTimer(0);
}
//---------------------------------------------------------------------------
void TFormSimStagecraftAbout::DrawBackground()
{
  TImage * const image = ImageBackground;

  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    const double yD = static_cast<double>(y);

    for (int x = 0; x != maxx; ++x)
    {
      const double xD = static_cast<double>(x);
      //Range z: -3 , +3
      const double zD
        = std::cos(xD / 3.0)
        + std::sin(yD / 4.0)
        - std::sin( (xD + yD) / 5.0);
      const int grey = static_cast<int>( (zD + 3.0) * (256.0 / 6.0) );
      assert(grey >=   0);
      assert(grey <  256);
      myLine[x*3+2] = (myLine[x*3+2] + grey) % 256; //Red
      myLine[x*3+1] = (myLine[x*3+1] + grey) % 256; //Green
      myLine[x*3+0] = (myLine[x*3+0] + grey) % 256; //Blue
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftAbout::TimerColorTimer(TObject *Sender)
{
  static int tick = 0;
  ++tick;

  switch (tick % 15)
  {
    case  0: mDr =  3; mDg = -4; mDb =  2; break;
    case  1: mDr =  4; mDg = -3; mDb =  1; break;
    case  2: mDr =  5; mDg = -2; mDb = -1; break;
    case  3: mDr =  4; mDg =  1; mDb = -2; break;
    case  4: mDr =  3; mDg =  2; mDb = -3; break;
    case  5: mDr =  2; mDg =  3; mDb = -4; break;
    case  6: mDr =  1; mDg =  4; mDb = -3; break;
    case  7: mDr = -1; mDg =  5; mDb = -2; break;
    case  8: mDr = -2; mDg =  4; mDb =  1; break;
    case  9: mDr = -3; mDg =  3; mDb =  2; break;
    case 10: mDr = -4; mDg =  2; mDb =  3; break;
    case 11: mDr = -3; mDg =  1; mDb =  4; break;
    case 12: mDr = -2; mDg = -1; mDb =  5; break;
    case 13: mDr =  1; mDg = -2; mDb =  4; break;
    case 14: mDr =  2; mDg = -3; mDb =  3; break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftAbout::TimerMainTimer(TObject *Sender)
{
  TImage * const image = ImageBackground;

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
      myLine[x*3+2]+=mDr; //Red
      myLine[x*3+1]+=mDg; //Green
      myLine[x*3+0]+=mDb; //Blue
    }
  }

  this->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftAbout::ButtonWhatsNewClick(
      TObject *Sender)
{
  boost::shared_ptr<TFormSimStagecraftWhatsNew> f(
    new TFormSimStagecraftWhatsNew(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TFormSimStagecraftAbout::ButtonOtherLicencesClick(
      TObject *Sender)
{
  boost::shared_ptr<TFormSimStagecraftOtherLicences> f(
    new TFormSimStagecraftOtherLicences(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
/*
= About SimStagecraft =

Some technical information about SimStagecraft

== Project ==

In 'Project | Forms | Auto-create Forms' the following Forms
should appear, in this order:
- FormSimStagecraftMenu
- FormSprites
All other Forms must be in the 'Available Forms' collumn


*/

