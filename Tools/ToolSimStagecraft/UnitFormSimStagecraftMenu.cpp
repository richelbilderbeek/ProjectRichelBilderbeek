//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <cmath>
#include <boost/scoped_ptr.hpp>
#include "UnitVcl.h"
#include "UnitFormSimStagecraftMenu.h"
#include "UnitFormSimStagecraftSelect.h"
#include "UnitFormSimStagecraftAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimStagecraftMenu *FormSimStagecraftMenu;
//---------------------------------------------------------------------------
__fastcall TFormSimStagecraftMenu::TFormSimStagecraftMenu(TComponent* Owner)
  : TForm(Owner), mImages(this->GetImages()), mBorderSize(8)
{
  OnResize(0);
  DrawScreen();
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMenu::DrawScreen()
{
  //Draw background
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  //Draw images
  typedef std::vector<TImage*>::const_iterator Iterator;
  const Iterator j = mImages.end();
  for (Iterator i = mImages.begin(); i!=j; ++i)
  {
    ImageBuffer->Canvas->Draw( (*i)->Left, (*i)->Top, (*i)->Picture->Graphic);
  }

  //Put buffer on screen
  this->Canvas->Draw(mBorderSize,mBorderSize,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void TFormSimStagecraftMenu::PaintBackground()
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
        = std::cos(xD / 30.0)
        + std::sin(yD / 45.0)
        - std::sin( (xD + yD) / 60.0);
      const int grey = static_cast<int>( (zD + 3.0) * (256.0 / 6.0) );
      assert(grey >=   0);
      assert(grey <  256);
      myLine[x*3+2] = grey; //Red
      myLine[x*3+1] = grey; //Green
      myLine[x*3+0] = grey; //Blue
    }
  }
}
//---------------------------------------------------------------------------}
void TFormSimStagecraftMenu::TickBackground()
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
      ++myLine[x*3+2]; //Red
      ++myLine[x*3+1]; //Green
      ++myLine[x*3+0]; //Blue
    }
  }
}
//---------------------------------------------------------------------------}

void __fastcall TFormSimStagecraftMenu::FormResize(TObject *Sender)
{
  ImageBackground->Picture->Bitmap->Width  = ClientWidth - (mBorderSize * 2);
  ImageBackground->Picture->Bitmap->Height = ClientHeight - (mBorderSize * 2);
  ImageBuffer->Picture->Bitmap->Width  = ClientWidth - (mBorderSize * 2);
  ImageBuffer->Picture->Bitmap->Height = ClientHeight - (mBorderSize * 2);
  PaintBackground();
}
//---------------------------------------------------------------------------

void __fastcall TFormSimStagecraftMenu::TimerBackgroundTimer(TObject *Sender)
{
  TickBackground();
  DrawScreen();
}
//---------------------------------------------------------------------------
const std::vector<TImage*> TFormSimStagecraftMenu::GetImages() const
{
  std::vector<TImage*> v;
  v.push_back(ImageStart);
  v.push_back(ImageAbout);
  v.push_back(ImageQuit);
  v.push_back(ImageTitle);
  v.push_back(Image1);
  v.push_back(Image2);
  v.push_back(Image3);
  v.push_back(Image4);
  v.push_back(Image5);
  v.push_back(Image6);
  return v;
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftMenu::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (OnImage(X,Y,ImageStart) == true
   || OnImage(X,Y,Image1    ) == true
   || OnImage(X,Y,Image4    ) == true)
  {
    //Start game
    TimerBackground->Enabled = false;
    boost::scoped_ptr<TFormSimStagecraftSelect> form(new TFormSimStagecraftSelect(0));
    form->ShowModal();
    TimerBackground->Enabled = true;
  }
  else
  if (OnImage(X,Y,ImageAbout) == true
   || OnImage(X,Y,Image2    ) == true
   || OnImage(X,Y,Image5    ) == true)
  {
    //About screen
    TimerBackground->Enabled = false;
    boost::scoped_ptr<TFormSimStagecraftAbout> form(new TFormSimStagecraftAbout(0));
    form->ShowModal();
    TimerBackground->Enabled = true;
  }
  else
  if (OnImage(X,Y,ImageQuit) == true
   || OnImage(X,Y,Image3   ) == true
   || OnImage(X,Y,Image6   ) == true)
  {
    Close();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftMenu::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  switch (Key)
  {
    case 'S': case 's': case '1': case VK_F1:
      FormMouseDown(0,TMouseButton(),TShiftState(),
        ImageStart->Left, ImageStart->Top);
      break;
    case 'A': case 'a': case '2': case VK_F2:
      FormMouseDown(0,TMouseButton(),TShiftState(),
        ImageAbout->Left, ImageAbout->Top);
      break;
    case 'Q':
    case '3': case VK_F3:
      FormMouseDown(0,TMouseButton(),TShiftState(),
        ImageQuit->Left, ImageQuit->Top);
      break;
  }

}
//---------------------------------------------------------------------------


