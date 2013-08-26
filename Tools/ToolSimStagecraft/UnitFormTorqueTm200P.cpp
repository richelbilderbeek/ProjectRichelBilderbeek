//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <cmath>
#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitDisplayControl.h"
#include "UnitMachine.h"
#include "UnitSpeaker.h"
#include "UnitVcl.h"
#include "UnitFormTorqueTm200P.h"
#include "UnitFormMachine.h"
#include "UnitFormSprites.h"

#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormMachine"
#pragma resource "*.dfm"
TFormTorqueTm200P *FormTorqueTm200P;
//---------------------------------------------------------------------------
__fastcall TFormTorqueTm200P::TFormTorqueTm200P(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSpeaker(boost::shared_ptr<SpeakerRcf322A>(new SpeakerRcf322A))
{
  //Control
  mPowerSwitch = boost::shared_ptr<TwoSwitchControl>(
    new TwoSwitchControl(this,
      mSpeaker->mPowerSwitch,ImagePowerSwitch));
  mVolumeDial = boost::shared_ptr<DialControl>(
    new DialControl(this,
      mSpeaker->mVolumeDial,ImageVolumeDial));
  //Connect
  mEuroMale = boost::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSpeaker->mEuroMalePower,ImageEuroMale));
  mXlrFemale = boost::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSpeaker->mXlrInput,ImageXlrFemale));
  mXlrMale = boost::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSpeaker->mXlrDaisyChain,ImageXlrMale));
  //Display
  mLedPower = boost::shared_ptr<LedControl>(new LedControl(
    mSpeaker->mLedPower,ImageLedPower));
  mLedLimProt = boost::shared_ptr<LedControl>(new LedControl(
    mSpeaker->mLedLimProt,ImageLedLimProt));


  CreateWatermark(ImageView,ImageWatermark);

  ImageVolumeDial->Picture->Bitmap->Width  = 50;
  ImageVolumeDial->Picture->Bitmap->Height = 50;
  ImageVolumeDial->Transparent = true;

  //Set controls by clicking virtually
  mVolumeDial->OnMouseDown(
    1 * ImageVolumeDial->Picture->Bitmap->Width  / 4,
    3 * ImageVolumeDial->Picture->Bitmap->Height / 4);
  mPowerSwitch->OnMouseDown(0,0);
}
//---------------------------------------------------------------------------
void TFormTorqueTm200P::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update all
      mLedPower->Update();
      mLedLimProt->Update();
      DrawAudioSignal(ImageSound,mSpeaker->GetSoundLevel());
      //Start drawing
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageVolumeDial);
      DrawOnBuffer(ImagePowerSwitch);
      DrawOnBuffer(ImageSound);
      DrawOnBuffer(ImageLedPower);
      DrawOnBuffer(ImageLedLimProt);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageXlrFemale);
      DrawOnBuffer(ImageXlrMale);
      DrawOnBuffer(ImageEuroMale);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormTorqueTm200P::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageVolumeDial))
      {
        mVolumeDial->OnMouseDown(
          x - ImageVolumeDial->Left,
          y - ImageVolumeDial->Top);
      }
      else if (OnImage(x,y,ImagePowerSwitch))
      {
        mPowerSwitch->OnMouseDown(
          x - ImagePowerSwitch->Left,
          y - ImagePowerSwitch->Top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageXlrMale)) mFormParent->OnConnectorClick(mXlrMale.get());
      if (OnImage(x,y,ImageXlrFemale)) mFormParent->OnConnectorClick(mXlrFemale.get());
      if (OnImage(x,y,ImageEuroMale)) mFormParent->OnConnectorClick(mEuroMale.get());
      break;
  }
}
//---------------------------------------------------------------------------

