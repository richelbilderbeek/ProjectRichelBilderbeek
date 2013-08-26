//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitSoundTable.h"
#include "UnitFormAlesisMultimix8.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAlesisMultimix8 *FormAlesisMultimix8;
//---------------------------------------------------------------------------
__fastcall TFormAlesisMultimix8::TFormAlesisMultimix8(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSoundTable(boost::shared_ptr<SoundTableEasySound>(new SoundTableEasySound))
{

  //Control
  mFaderControl1 = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFader1,ImageFader1));
  mFaderControlMaster = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFaderMaster,ImageFaderMaster));
  //Connect
  mEuroMalePower = boost::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSoundTable->mPower,ImageEuroMalePower));
  mXlrFemaleMic1 = boost::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSoundTable->mMic1,ImageXlrFemaleMic1));
  mXlrMaleMasterLeft = boost::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterL,ImageXlrMaleMasterLeft));
  mXlrMaleMasterRight = boost::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterR,ImageXlrMaleMasterRight));
  //Display
  mAudioSignalDisplay = boost::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mSoundTable->mAudioSignalDisplay,ImageAudioSignal));

  CreateWatermark(ImageView,ImageWatermark);

  //Make some images transparent
  ImageConnectMic->Picture->Bitmap->TransparentColor = clWhite;
  ImageConnect1->Picture->Bitmap->TransparentColor = clWhite;
  ImageConnectMaster->Picture->Bitmap->TransparentColor = clWhite;
  ImageConnectL->Picture->Bitmap->TransparentColor = clWhite;
  ImageConnectR->Picture->Bitmap->TransparentColor = clWhite;
  ImageConnectPower->Picture->Bitmap->TransparentColor = clWhite;
  ImageUse1->Picture->Bitmap->TransparentColor = clWhite;
  ImageUseMaster->Picture->Bitmap->TransparentColor = clWhite;
  ImageConnectMic->Transparent = true;
  ImageConnect1->Transparent = true;
  ImageConnectMaster->Transparent = true;
  ImageConnectL->Transparent = true;
  ImageConnectR->Transparent = true;
  ImageConnectPower->Transparent = true;
  ImageUse1->Transparent = true;
  ImageUseMaster->Transparent = true;
  OnResize(0);
  //Manually set the faders
  mFaderControl1->OnMouseDown(0,ImageFader1->Picture->Bitmap->Height - 1);
  mFaderControlMaster->OnMouseDown(0,ImageFaderMaster->Picture->Bitmap->Height - 1);
}
//---------------------------------------------------------------------------
void TFormAlesisMultimix8::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update displays
      mAudioSignalDisplay->Update();
      //Draw
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageFader1);
      DrawOnBuffer(ImageAudioSignal);
      DrawOnBuffer(ImageFaderMaster);
      DrawOnBuffer(ImageUse1);
      DrawOnBuffer(ImageUseMaster);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageXlrFemaleMic1);
      DrawOnBuffer(ImageXlrMaleMasterLeft);
      DrawOnBuffer(ImageXlrMaleMasterRight);
      DrawOnBuffer(ImageEuroMalePower);
      DrawOnBuffer(ImageConnectMic);
      DrawOnBuffer(ImageConnect1);
      DrawOnBuffer(ImageConnectMaster);
      DrawOnBuffer(ImageConnectL);
      DrawOnBuffer(ImageConnectR);
      DrawOnBuffer(ImageConnectPower);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormAlesisMultimix8::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageFader1))
      {
        mFaderControl1->OnMouseDown(
          x - ImageFader1->Left,
          y - ImageFader1->Top);
      }
      else if (OnImage(x,y,ImageFaderMaster))
      {
        mFaderControlMaster->OnMouseDown(
          x - ImageFaderMaster->Left,
          y - ImageFaderMaster->Top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageXlrFemaleMic1))
        mFormParent->OnConnectorClick(mXlrFemaleMic1.get());
      if (OnImage(x,y,ImageXlrMaleMasterLeft))
        mFormParent->OnConnectorClick(mXlrMaleMasterLeft.get());
      if (OnImage(x,y,ImageXlrMaleMasterRight))
        mFormParent->OnConnectorClick(mXlrMaleMasterRight.get());
      if (OnImage(x,y,ImageEuroMalePower))
        mFormParent->OnConnectorClick(mEuroMalePower.get());
      break;
  }
}
//---------------------------------------------------------------------------
void TFormAlesisMultimix8::OnAfterResize()
{
  //Use
  {
    const std::vector<TRect> v(GetRectsHorizontal(ClientRect,3));
    PlaceInCenter(ImageAudioSignal,v[2]);
    const std::vector<TRect> v1(GetRectsVertical(v[0],5));
    const std::vector<TRect> v2(GetRectsVertical(v[1],5));
    ImageFader1->Picture->Bitmap->Height = MergeRects(v1[1],v1[3]).Height();
    ImageFader1->Refresh();
    ImageFaderMaster->Picture->Bitmap->Height = MergeRects(v2[1],v2[3]).Height();
    ImageFaderMaster->Refresh();
    PlaceInCenter(ImageUse1  ,v1[0]);
    PlaceInCenter(ImageFader1,MergeRects(v1[1],v1[3]));
    PlaceInCenter(ImageUseMaster  ,v2[0]);
    PlaceInCenter(ImageFaderMaster,MergeRects(v2[1],v2[3]));
  }
  //Connect
  {
    const std::vector<TRect> v(GetRectsHorizontal(ClientRect,4));
    const std::vector<TRect> v0(GetRectsVertical(v[0],6));
    const std::vector<TRect> v1(GetRectsVertical(v[1],6));
    const std::vector<TRect> v2(GetRectsVertical(v[2],6));
    const std::vector<TRect> v3(GetRectsVertical(v[3],6));
    PlaceInCenter(ImageConnectMic   ,v0[1]);
    PlaceInCenter(ImageConnect1     ,v0[2]);
    PlaceInCenter(ImageConnectMaster,MergeRects(v1[1],v2[1]));
    PlaceInCenter(ImageConnectL     ,v1[2]);
    PlaceInCenter(ImageConnectR     ,v2[2]);
    PlaceInCenter(ImageConnectPower ,v3[2]);
    PlaceInCenter(ImageXlrFemaleMic1     ,MergeRects(v0[3],v0[4]));
    PlaceInCenter(ImageXlrMaleMasterLeft ,MergeRects(v1[3],v1[4]));
    PlaceInCenter(ImageXlrMaleMasterRight,MergeRects(v2[3],v2[4]));
    PlaceInCenter(ImageEuroMalePower     ,MergeRects(v3[3],v3[4]));
  }
}
//---------------------------------------------------------------------------





