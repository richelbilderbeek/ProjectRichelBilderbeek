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
#include "UnitFormRcf322A.h"
#include "UnitFormMachine.h"
#include "UnitFormSprites.h"

#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormMachine"
#pragma resource "*.dfm"
TFormRcf322A *FormRcf322A;
//---------------------------------------------------------------------------
__fastcall TFormRcf322A::TFormRcf322A(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSpeaker(boost::shared_ptr<Rcf322A>(new Rcf322A))
{
  //Control
  mPowerSwitch = boost::shared_ptr<TwoSwitchControl>(
    new TwoSwitchControl(this,
      mSpeaker->mPowerSwitch,ImageTwoSwitchPower));
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
  mJackFemale = boost::shared_ptr<JackFemaleControl>(
    new JackFemaleControl(this,mSpeaker->mJackInput,ImageJackFemale));
  //Display
  mLedPower = boost::shared_ptr<LedControl>(new LedControl(
    mSpeaker->mLedPower,ImageLedPower));
  mLedLimProt = boost::shared_ptr<LedControl>(new LedControl(
    mSpeaker->mLedLimProt,ImageLedLimProt));


  CreateWatermark(ImageView,ImageWatermark);

  ImageVolumeDial->Picture->Bitmap->Width  = 50;
  ImageVolumeDial->Picture->Bitmap->Height = 50;
  ImageVolumeDial->Transparent = true;

  OnResize(0);

  //Set controls by clicking virtually
  mVolumeDial->OnMouseDown(
    1 * ImageVolumeDial->Picture->Bitmap->Width  / 4,
    3 * ImageVolumeDial->Picture->Bitmap->Height / 4);
  mPowerSwitch->OnMouseDown(0,0);
}
//---------------------------------------------------------------------------
void TFormRcf322A::UpdateBuffer()
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
      //Labels
      DrawOnBuffer(LabelUseVolume);
      DrawOnBuffer(LabelUsePowerOn);
      DrawOnBuffer(LabelUseLimProt);
      //Controls
      DrawOnBuffer(ImageVolumeDial);
      DrawOnBuffer(ImageTwoSwitchPower);
      DrawOnBuffer(ImageSound);
      DrawOnBuffer(ImageLedPower);
      DrawOnBuffer(ImageLedLimProt);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer(LabelConnectBalanced);
      DrawOnBuffer(LabelConnectMains);
      //Connectors
      DrawOnBuffer(ImageXlrFemale);
      DrawOnBuffer(ImageXlrMale);
      DrawOnBuffer(ImageEuroMale);
      DrawOnBuffer(ImageJackFemale);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormRcf322A::OnMouseDown(const int x, const int y)
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
      else if (OnImage(x,y,ImageTwoSwitchPower))
      {
        mPowerSwitch->OnMouseDown(
          x - ImageTwoSwitchPower->Left,
          y - ImageTwoSwitchPower->Top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageXlrMale   )) mFormParent->OnConnectorClick(mXlrMale.get()   );
      if (OnImage(x,y,ImageXlrFemale )) mFormParent->OnConnectorClick(mXlrFemale.get() );
      if (OnImage(x,y,ImageEuroMale  )) mFormParent->OnConnectorClick(mEuroMale.get()  );
      if (OnImage(x,y,ImageJackFemale)) mFormParent->OnConnectorClick(mJackFemale.get());
      break;
  }
}
//---------------------------------------------------------------------------
void TFormRcf322A::OnAfterResize()
{
  //Use
  {
    //Get y-x-ordered vector of TRects
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,2,6));
    //Resize bitmaps
      //ImageFader1->Picture->Bitmap->Height      = MergeRects(v[3][2],v[5][2]).Height();
      //ImageFader1->Refresh();
    //Place bitmaps
    //Labels
    PlaceInCenter(LabelUseVolume,v[0][0]);
    PlaceInCenter(LabelUsePowerOn,v[2][1]);
    PlaceInCenter(LabelUseLimProt,v[4][1]);
    //Controls
    PlaceInCenter(ImageVolumeDial,v[1][0]);
    PlaceInCenter(ImageTwoSwitchPower,v[4][0]);
    //Displays
    PlaceInCenter(ImageSound,MergeRects(v[0][1],v[1][1]));
    PlaceInCenter(ImageLedPower,v[3][1]);
    PlaceInCenter(ImageLedLimProt,v[5][1]);
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,1,6));
    //Labels
    PlaceInCenter(LabelConnectBalanced  ,v[0][0]);
    PlaceInCenter(LabelConnectMains     ,v[4][0]);
    //Connectors
    PlaceInCenter(ImageJackFemale,v[1][0]);
    PlaceInCenter(ImageXlrFemale ,v[2][0]);
    PlaceInCenter(ImageXlrMale   ,v[3][0]);
    PlaceInCenter(ImageEuroMale  ,v[5][0]);
  }
}
//---------------------------------------------------------------------------

