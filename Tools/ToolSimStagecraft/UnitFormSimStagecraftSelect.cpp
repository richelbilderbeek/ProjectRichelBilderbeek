//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include <cmath>
#include <cassert>
#include <stdexcept>
#include <boost/scoped_ptr.hpp>
#include "UnitFormSimStagecraftMain.h"
#include "UnitFormSimStagecraftSelect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimStagecraftSelect *FormSimStagecraftSelect;
//---------------------------------------------------------------------------
__fastcall TFormSimStagecraftSelect::TFormSimStagecraftSelect(TComponent* Owner)
  : TForm(Owner), mBorderSize(8), mLevel(1)
{
  mImages.push_back(ImageSelectLevel);
  mImages.push_back(ImageArrowLeft);
  mImages.push_back(ImageArrowRight);
  mImages.push_back(ImageSelectLeft);
  mImages.push_back(ImageSelectRight);
  mImages.push_back(ImageStart);
  mImages.push_back(ImageQuit);
  mImages.push_back(ImageLed1);
  mImages.push_back(ImageLed2);
  mImages.push_back(ImageLed3);
  mImages.push_back(ImageLed4);

  OnResize(0);
  UpdateText();
}
//---------------------------------------------------------------------------
void TFormSimStagecraftSelect::DrawScreen()
{
  //Draw background on buffer
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  //Draw all sprites on buffer
  typedef std::vector<TImage*>::iterator Iterator;
  const Iterator j = mImages.end();
  for (Iterator i = mImages.begin(); i!=j; ++i)
  {
    ImageBuffer->Canvas->Draw(
      (*i)->Left,
      (*i)->Top,
      (*i)->Picture->Graphic);
  }

  //Draw buffer on screen
  this->Canvas->Draw(mBorderSize,mBorderSize,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
TImage * const TFormSimStagecraftSelect::GetImage(const int value) const
{
  switch (value)
  {
    case 0: return Image0;
    case 1: return Image1;
    case 2: return Image2;
    case 3: return Image3;
    case 4: return Image4;
    case 5: return Image5;
    case 6: return Image6;
    case 7: return Image7;
    case 8: return Image8;
    case 9: return Image9;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unhandled value in TFormSimStagecraftSelect::GetImage");
}
//---------------------------------------------------------------------------
const bool TFormSimStagecraftSelect::OnImage(const int x, const int y,
  const TImage * const image) const
{
  return ( x >= image->Left
    && x < image->Left + image->Width
    && y >= image->Top
    && y < image->Top + image->Height);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftSelect::FormResize(TObject *Sender)
{
  ImageBackground->Picture->Bitmap->Width
    = ClientWidth  - (mBorderSize * 2);
  ImageBackground->Picture->Bitmap->Height
    = RichEdit->Top - (mBorderSize * 2);
  ImageBuffer->Picture->Bitmap->Width
    = ClientWidth  - (mBorderSize * 2);
  ImageBuffer->Picture->Bitmap->Height
    = RichEdit->Top - (mBorderSize * 2);
  PaintBackground();
}
//---------------------------------------------------------------------------
void __fastcall TFormSimStagecraftSelect::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (OnImage(X,Y,ImageStart)==true)
  {
    //Turn timer off temporarily
    TimerMain->Enabled = false;
    boost::scoped_ptr<TFormSimStagecraftMain> form(
      new TFormSimStagecraftMain(0,IntToStr(mLevel)));
    form->ShowModal();

    //And turn it back on
    TimerMain->Enabled = true;
  }
  else if (OnImage(X,Y,ImageArrowLeft)==true && mLevel > 1)
  {
    --mLevel;
    ImageSelectLeft->Picture  = GetImage(mLevel / 10)->Picture;
    ImageSelectRight->Picture = GetImage(mLevel % 10)->Picture;

    UpdateText();
    DrawScreen();
  }
  else if (OnImage(X,Y,ImageArrowRight)==true && mLevel < 99)
  {
    ++mLevel;
    ImageSelectLeft->Picture  = GetImage(mLevel / 10)->Picture;
    ImageSelectRight->Picture = GetImage(mLevel % 10)->Picture;
    UpdateText();
    DrawScreen();
  }
  else if (OnImage(X,Y,ImageQuit)==true)
  {
    Close();
  }
}
//---------------------------------------------------------------------------
void TFormSimStagecraftSelect::UpdateText()
{
  RichEdit->Clear();
  switch (mLevel)
  {
    case 1:
      RichEdit->Lines->Add("Level 1: Connect a lamp to a socket");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Fresnel");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 2:
      RichEdit->Lines->Add("Level 2: Connect a microphone to an active speaker");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Microphone, ShureSm58");
      RichEdit->Lines->Add("- Active speaker, RCF322A");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 3:
      RichEdit->Lines->Add("Level 3: Connect and use a simple sound table");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Microphone, ShureSm58");
      RichEdit->Lines->Add("- Active speaker, RCF322A");
      RichEdit->Lines->Add("- Soundtable, SimpleSound1");
      RichEdit->Lines->Add("- Triplet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 4:
      RichEdit->Lines->Add("Level 4: Connect and use a simple light table");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Lighttable, SimpleShine");
      RichEdit->Lines->Add("- Dimmerpack, Dimblock V3");
      RichEdit->Lines->Add("- 5x fresnel");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, power current");
      break;
    case 5:
      RichEdit->Lines->Add("Level 5: Connect and use a more advanced sound table");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- 2x microphone, ShureSm58");
      RichEdit->Lines->Add("- 2x active speaker, RCF322A");
      RichEdit->Lines->Add("- Soundtable, SimpleSound2");
      RichEdit->Lines->Add("- Triplet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 6:
      RichEdit->Lines->Add("Level 6: Send sound using AUX");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Microphone, ShureSm58");
      RichEdit->Lines->Add("- Active speaker, RCF322A");
      RichEdit->Lines->Add("- Soundtable, SimpleSound3");
      RichEdit->Lines->Add("- Triplet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 7:
      RichEdit->Lines->Add("Level 7: Serve three singers, send sound to PA and monitors");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- 3x microphone, ShureSm58");
      RichEdit->Lines->Add("- 4x active speaker, RCF322A");
      RichEdit->Lines->Add("- Soundtable, SimpleSound3");
      RichEdit->Lines->Add("- Octet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 8:
      RichEdit->Lines->Add("Level 8: Connect a CD player to speakers");
      RichEdit->Lines->Add("  using a transition piece");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Active speaker, RCF322A");
      RichEdit->Lines->Add("- CD player");
      RichEdit->Lines->Add("- Transition piece: jack male to 2x cinch female");
      RichEdit->Lines->Add("- Octet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 9:
      RichEdit->Lines->Add("Level 9: Connect a CD player to speakers");
      RichEdit->Lines->Add("  using a sound table");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Active speaker, RCF322A");
      RichEdit->Lines->Add("- CD player");
      RichEdit->Lines->Add("- Soundtable, SimpleSound4");
      RichEdit->Lines->Add("- Octet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 10:
      RichEdit->Lines->Add("Level 10: Record an MD from CD");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- CD player");
      RichEdit->Lines->Add("- MD player");
      RichEdit->Lines->Add("- Transition piece: jack male to 2x cinch female");
      RichEdit->Lines->Add("- Active speaker, RCF322A");
      RichEdit->Lines->Add("- Octet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 11:
      RichEdit->Lines->Add("Level 11: Record an MD from CD and microphone");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Microphone, ShureSm58");
      RichEdit->Lines->Add("- MD player");
      RichEdit->Lines->Add("- Transition piece: jack male to 2x cinch female");
      RichEdit->Lines->Add("- Soundtable, SimpleSound4");
      RichEdit->Lines->Add("- Active speaker, RCF322A");
      RichEdit->Lines->Add("- Octet, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
    case 12:
      RichEdit->Lines->Add("Level 12: Learn to use the crossfader");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Lighttable, SimpleShine2");
      RichEdit->Lines->Add("- Dimmerpack, Dimblock V3");
      RichEdit->Lines->Add("- 5x fresnel");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      RichEdit->Lines->Add("- Wall socket, power current");
      break;
    case 13:
      RichEdit->Lines->Add("Level 13: Connect a microphone to a passive speaker");
      RichEdit->Lines->Add("");
      RichEdit->Lines->Add("Equipment:");
      RichEdit->Lines->Add("- Microphone, ShureSm58");
      RichEdit->Lines->Add("- Passive speaker, RCF Event 3000");
      RichEdit->Lines->Add("- Amplifier, EasyAmp");
      RichEdit->Lines->Add("- Wall socket, 220 Volts");
      break;
  }
}
//---------------------------------------------------------------------------
void TFormSimStagecraftSelect::PaintBackground()
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
void TFormSimStagecraftSelect::TickBackground()
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
void __fastcall TFormSimStagecraftSelect::TimerMainTimer(TObject *Sender)
{
  TickBackground();
  DrawScreen();
}
//---------------------------------------------------------------------------

void __fastcall TFormSimStagecraftSelect::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  switch (Key)
  {
    case 'S': case 's': case '1': case VK_F1:
      FormMouseDown(0,TMouseButton(),TShiftState(),
        ImageStart->Left, ImageStart->Top);
      break;
    case '-': case VK_LEFT:
      FormMouseDown(0,TMouseButton(),TShiftState(),
        ImageArrowLeft->Left, ImageArrowLeft->Top);
      break;
    case '+': case VK_RIGHT:
      FormMouseDown(0,TMouseButton(),TShiftState(),
        ImageArrowRight->Left, ImageArrowRight->Top);
      break;
    case 'Q': case '2': case VK_F2:
      FormMouseDown(0,TMouseButton(),TShiftState(),
        ImageQuit->Left, ImageQuit->Top);
      break;
  }
}
//---------------------------------------------------------------------------


