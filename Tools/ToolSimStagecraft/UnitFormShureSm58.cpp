//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitMicrophone.h"
#include "UnitFunctions.h"
#include "UnitVcl.h"
#include "UnitFormShureSm58.h"
#include "UnitFormSprites.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormShureSm58 *FormShureSm58;
//---------------------------------------------------------------------------
__fastcall TFormShureSm58::TFormShureSm58(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mMicrophone(boost::shared_ptr<ShureSm58>(new ShureSm58)),
    mSinging(false),
    mSingerAverage( 0.4 + GetRandomUniform() * 0.6)
{
  //Use
  //Connect
  mXlrMale = boost::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mMicrophone->mXlrInput,ImageXlrMale));

  OnResize(0);

  CreateWatermark(ImageView,ImageWatermark);
}
//---------------------------------------------------------------------------
void TFormShureSm58::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView   :
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse    :
      //Set new audio signal
      DrawAudioSignal(ImageAudioSignal,mMicrophone->GetAudioSignalStrength());
      //Draw 'Use' images
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageSing);
      DrawOnBuffer(ImageAudioSignal);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageXlrMale);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
  //Drawing is done by TFormSimStagecraftMain
}
//---------------------------------------------------------------------------
void TFormShureSm58::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageSing))
      {
        if (mSinging == true)
        {
          mSinging = false;
          mMicrophone->SetAudioSignalStrength(0.0);
          ImageSing->Picture = FormSprites->ImageSingNo->Picture;
        }
        else
        {
          mSinging = true;
          mMicrophone->SetAudioSignalStrength(1.0);
          ImageSing->Picture = FormSprites->ImageSingYes->Picture;
        }
        mFormParent->OnControllerClick();
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageXlrMale))
      {
        mFormParent->OnConnectorClick(mXlrMale.get());
      }
      break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormShureSm58::TimerSingTimer(TObject *Sender)
{
  //This singer sings at a strength of mSingerAverage
  // plus or minus 0.5 * mSingerAverage
  const double audioSignalStrength = (mSinging == true
    ? (0.5 * mSingerAverage) + (GetRandomUniform() * mSingerAverage)
    : 0.0);
  mMicrophone->SetAudioSignalStrength(audioSignalStrength);
  DrawAudioSignal(ImageAudioSignal,mMicrophone->GetAudioSignalStrength());
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
void TFormShureSm58::OnAfterResize()
{
  const std::vector<TRect> v(GetRectsHorizontal(ClientRect,2));
  PlaceInCenter(ImageSing,v[0]);
  PlaceInCenter(ImageAudioSignal,v[1]);
  PlaceInCenter(ImageXlrMale,ClientRect);
}
//---------------------------------------------------------------------------


