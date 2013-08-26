//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitFormEasyAmp.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitAmplifier.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormMachine"
#pragma resource "*.dfm"
TFormEasyAmp *FormEasyAmp;
//---------------------------------------------------------------------------
__fastcall TFormEasyAmp::TFormEasyAmp(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mAmplifier(boost::shared_ptr<EasyAmp>(new EasyAmp))
{


  //Control
  mPowerSwitch = boost::shared_ptr<TwoSwitchControl>(
    new TwoSwitchControl(this,mAmplifier->mPowerSwitch,ImagePowerSwitch));
    boost::shared_ptr<DialControl> mGain;
  this->mGain = boost::shared_ptr<DialControl>(
    new DialControl(this,mAmplifier->mGain,ImageGain));
  assert(this->mGain);
  //Connect
  mEuro = boost::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mAmplifier->mEuroPower,ImageEuro));
  mJackXlrL = boost::shared_ptr<JackXlrFemaleControl>(
    new JackXlrFemaleControl(this,mAmplifier->mJackXlrL,ImageJackXlrL));
  mJackXlrR = boost::shared_ptr<JackXlrFemaleControl>(
    new JackXlrFemaleControl(this,mAmplifier->mJackXlrR,ImageJackXlrR));
  mSpeakonL = boost::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mAmplifier->mSpeakonL,ImageSpeakonL));
  mSpeakonR = boost::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mAmplifier->mSpeakonR,ImageSpeakonR));
  //Display
  mLedPower = boost::shared_ptr<LedControl> (
    new LedControl(mAmplifier->mLedPower,ImageLed));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);

  //Set controls by clicking virtually
  //Strange, if I remove 'this' I get access violations,
  //  because mGain is null (where this->mGain is not)
  this->mGain->OnMouseDown(
    1 * ImageGain->Picture->Bitmap->Width  / 4,
    3 * ImageGain->Picture->Bitmap->Height / 4);
  mPowerSwitch->OnMouseDown(0,0);
}
//---------------------------------------------------------------------------
void TFormEasyAmp::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update displays
      mLedPower->Update();
      //Draw
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      //Controls
      DrawOnBuffer(ImagePowerSwitch);
      DrawOnBuffer(ImageGain);
      //Display
      DrawOnBuffer(ImageLed);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      //Connectors
      DrawOnBuffer(ImageEuro);
      DrawOnBuffer(ImageJackXlrL);
      DrawOnBuffer(ImageJackXlrR);
      DrawOnBuffer(ImageSpeakonL);
      DrawOnBuffer(ImageSpeakonR);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormEasyAmp::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImagePowerSwitch))
      {
        mPowerSwitch->OnMouseDown(
          x - ImagePowerSwitch->Left,
          y - ImagePowerSwitch->Top);
      }
      else if (OnImage(x,y,ImageGain))
      {
        assert(this->mGain);
        this->mGain->OnMouseDown(
          x - ImageGain->Left,
          y - ImageGain->Top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageEuro))
        mFormParent->OnConnectorClick(mEuro.get());
      else if (OnImage(x,y,ImageJackXlrL))
        mFormParent->OnConnectorClick(mJackXlrL.get());
      else if (OnImage(x,y,ImageJackXlrR))
        mFormParent->OnConnectorClick(mJackXlrR.get());
      else if (OnImage(x,y,ImageSpeakonL))
        mFormParent->OnConnectorClick(mSpeakonL.get());
      else if (OnImage(x,y,ImageSpeakonR))
        mFormParent->OnConnectorClick(mSpeakonR.get());
      break;
  }
}
//---------------------------------------------------------------------------
void TFormEasyAmp::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,3,1));
    //Resize bitmaps
    //Place bitmaps
    //Labels
    //Controls
    PlaceInCenter(ImagePowerSwitch,v[0][0]);
    PlaceInCenter(ImageGain,v[0][1]);
    //Others
    //Displays
    PlaceInCenter(ImageLed,v[0][2]);
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,3,2));
    //Labels
    //Connectors
    PlaceInCenter(ImageEuro,MergeRects(v[0][0],v[1][0]));
    PlaceInCenter(ImageJackXlrL,v[0][1]);
    PlaceInCenter(ImageJackXlrR,v[0][2]);
    PlaceInCenter(ImageSpeakonL,v[1][1]);
    PlaceInCenter(ImageSpeakonR,v[1][2]);
  }
}
//---------------------------------------------------------------------------

