//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitSimpleSound1.h"
#include "UnitFormSimpleSound1.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimpleSound1 *FormSimpleSound1;
//---------------------------------------------------------------------------
__fastcall TFormSimpleSound1::TFormSimpleSound1(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSoundTable(boost::shared_ptr<SimpleSound1>(new SimpleSound1))
{

  //Control
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
  OnResize(0);
  //Manually set the faders
  mFaderControlMaster->OnMouseDown(0,ImageFaderMaster->Picture->Bitmap->Height - 1);
}
//---------------------------------------------------------------------------
void TFormSimpleSound1::UpdateBuffer()
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
      //Labels
      DrawOnBuffer(LabelUseMaster);
      DrawOnBuffer(LabelUseSimpleSound1);
      //Controllers
      DrawOnBuffer(ImageFaderMaster);
      //Display
      DrawOnBuffer(ImageAudioSignal);
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
void TFormSimpleSound1::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageFaderMaster))
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
void TFormSimpleSound1::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,2,5));
    //Resize images
    ImageFaderMaster->Picture->Bitmap->Height = MergeRects(v[1][0],v[3][0]).Height();
    ImageFaderMaster->Refresh();
    //Placement
    PlaceInCenter(LabelUseMaster,v[0][0]);
    PlaceInCenter(LabelUseSimpleSound1,v[0][1]);
    PlaceInCenter(ImageAudioSignal,MergeRects(v[1][1],v[3][1]));
    PlaceInCenter(ImageFaderMaster,MergeRects(v[1][0],v[3][0]));
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,4,6));
    PlaceInCenter(ImageConnectMic   ,v[1][0]);
    PlaceInCenter(ImageConnect1     ,v[2][0]);
    PlaceInCenter(ImageConnectMaster,MergeRects(v[1][1],v[1][2]));
    PlaceInCenter(ImageConnectL     ,v[2][1]);
    PlaceInCenter(ImageConnectR     ,v[2][2]);
    PlaceInCenter(ImageConnectPower ,v[2][3]);
    PlaceInCenter(ImageXlrFemaleMic1     ,MergeRects(v[3][0],v[4][0]));
    PlaceInCenter(ImageXlrMaleMasterLeft ,MergeRects(v[3][1],v[4][1]));
    PlaceInCenter(ImageXlrMaleMasterRight,MergeRects(v[3][2],v[4][2]));
    PlaceInCenter(ImageEuroMalePower     ,MergeRects(v[3][3],v[4][3]));
  }
}
//---------------------------------------------------------------------------





