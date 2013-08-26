//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitSimpleSound2.h"
#include "UnitFormSimpleSound2.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimpleSound2 *FormSimpleSound2;
//---------------------------------------------------------------------------
__fastcall TFormSimpleSound2::TFormSimpleSound2(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSoundTable(boost::shared_ptr<SimpleSound2>(new SimpleSound2))
{

  //Control
  mFaderControl1 = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFader1,ImageFader1));
  mFaderControl2 = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFader2,ImageFader2));
  mPressButtonControl1 = boost::shared_ptr<PressButtonControl>(
    new PressButtonControl(this,mSoundTable->mPressButton1,ImagePressButton1));
  mPressButtonControl2 = boost::shared_ptr<PressButtonControl>(
    new PressButtonControl(this,mSoundTable->mPressButton2,ImagePressButton2));
  mDialControl1 = boost::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDial1,ImageDial1));
  mDialControl2 = boost::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDial2,ImageDial2));
  mFaderControlMaster = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFaderMaster,ImageFaderMaster));
  //Connect
  mEuroMalePower = boost::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSoundTable->mPower,ImageEuroMalePower));
  mXlrFemaleMic1 = boost::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSoundTable->mMic1,ImageXlrFemaleMic1));
  mXlrFemaleMic2 = boost::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSoundTable->mMic2,ImageXlrFemaleMic2));
  mXlrMaleMasterLeft = boost::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterL,ImageXlrMaleMasterLeft));
  mXlrMaleMasterRight = boost::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterR,ImageXlrMaleMasterRight));
  //Display
  mAudioSignalDisplay = boost::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mSoundTable->mAudioSignalDisplay,ImageAudioSignal));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
  //Manually set the faders
  mFaderControl1->OnMouseDown(0,ImageFader1->Picture->Bitmap->Height - 1);
  mFaderControl2->OnMouseDown(0,ImageFader2->Picture->Bitmap->Height - 1);
  mFaderControlMaster->OnMouseDown(0,ImageFaderMaster->Picture->Bitmap->Height - 1);
  //Press buttons in and out
  mPressButtonControl1->OnMouseDown(0,ImagePressButton1->Picture->Bitmap->Height - 1);
  mPressButtonControl2->OnMouseDown(0,ImagePressButton2->Picture->Bitmap->Height - 1);
  mPressButtonControl1->OnMouseDown(0,ImagePressButton1->Picture->Bitmap->Height - 1);
  mPressButtonControl2->OnMouseDown(0,ImagePressButton2->Picture->Bitmap->Height - 1);
  //Set the gains to 0.0
  mDialControl1->OnMouseDown(5,17);
  mDialControl2->OnMouseDown(5,17);
}
//---------------------------------------------------------------------------
void TFormSimpleSound2::UpdateBuffer()
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
      DrawOnBuffer(LabelUse1);
      DrawOnBuffer(LabelUse2);
      DrawOnBuffer(LabelUseGain);
      DrawOnBuffer(LabelUsePfl);
      DrawOnBuffer(LabelUseMaster);
      DrawOnBuffer(LabelUseSimpleSound2);
      //Controls
      DrawOnBuffer(ImageFader1);
      DrawOnBuffer(ImageFader2);
      DrawOnBuffer(ImageFaderMaster);
      DrawOnBuffer(ImageDial1);
      DrawOnBuffer(ImageDial2);
      DrawOnBuffer(ImagePressButton1);
      DrawOnBuffer(ImagePressButton2);
      //Display
      DrawOnBuffer(ImageAudioSignal);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer(LabelConnectMic1);
      DrawOnBuffer(LabelConnectMic2);
      DrawOnBuffer(LabelConnect1);
      DrawOnBuffer(LabelConnect2);
      DrawOnBuffer(LabelConnectMaster);
      DrawOnBuffer(LabelConnectL);
      DrawOnBuffer(LabelConnectR);
      DrawOnBuffer(LabelConnectPower);
      //Connectors
      DrawOnBuffer(ImageXlrFemaleMic1);
      DrawOnBuffer(ImageXlrFemaleMic2);
      DrawOnBuffer(ImageXlrMaleMasterLeft);
      DrawOnBuffer(ImageXlrMaleMasterRight);
      DrawOnBuffer(ImageEuroMalePower);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormSimpleSound2::OnMouseDown(const int x, const int y)
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
      else if (OnImage(x,y,ImageFader2))
      {
        mFaderControl2->OnMouseDown(
          x - ImageFader2->Left,
          y - ImageFader2->Top);
      }
      else if (OnImage(x,y,ImagePressButton1))
      {
        mPressButtonControl1->OnMouseDown(
          x - ImagePressButton1->Left,
          y - ImagePressButton1->Top);
      }
      else if (OnImage(x,y,ImagePressButton2))
      {
        mPressButtonControl2->OnMouseDown(
          x - ImagePressButton2->Left,
          y - ImagePressButton2->Top);
      }
      else if (OnImage(x,y,ImageDial1))
      {
        mDialControl1->OnMouseDown(
          x - ImageDial1->Left,
          y - ImageDial1->Top);
      }
      else if (OnImage(x,y,ImageDial2))
      {
        mDialControl2->OnMouseDown(
          x - ImageDial2->Left,
          y - ImageDial2->Top);
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
      if (OnImage(x,y,ImageXlrFemaleMic2))
        mFormParent->OnConnectorClick(mXlrFemaleMic2.get());
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
void TFormSimpleSound2::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,7,7));
    //Resize bitmaps
    ImageFader1->Picture->Bitmap->Height      = MergeRects(v[3][2],v[5][2]).Height();
    ImageFader2->Picture->Bitmap->Height      = MergeRects(v[3][3],v[5][3]).Height();
    ImageFaderMaster->Picture->Bitmap->Height = MergeRects(v[3][4],v[5][5]).Height();
    ImageFader1->Refresh();
    ImageFader2->Refresh();
    ImageFaderMaster->Refresh();
    //Place bitmaps
    //Labels
    PlaceInCenter(LabelUse1,v[0][2]);
    PlaceInCenter(LabelUse2,v[0][3]);
    PlaceInCenter(LabelUseMaster,MergeRects(v[2][4],v[2][5]));
    PlaceInCenter(LabelUseGain,MergeRects(v[1][0],v[1][1]));
    PlaceInCenter(LabelUsePfl,MergeRects(v[2][0],v[2][1]));
    PlaceInCenter(LabelUseSimpleSound2,MergeRects(v[0][4],v[1][6]));
    //Controls
    PlaceInCenter(ImageDial1,v[1][2]);
    PlaceInCenter(ImagePressButton1,v[2][2]);
    PlaceInCenter(ImageFader1,MergeRects(v[3][2],v[5][2]));
    PlaceInCenter(ImageDial2,v[1][3]);
    PlaceInCenter(ImagePressButton2,v[2][3]);
    PlaceInCenter(ImageFader2,MergeRects(v[3][3],v[5][3]));
    PlaceInCenter(ImageFaderMaster,MergeRects(v[3][4],v[5][5]));
    //Displays
    PlaceInCenter(ImageAudioSignal,MergeRects(v[3][6],v[5][6]));
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,5,3));
    //Labels
    PlaceInCenter(LabelConnectMic1  ,v[0][0]);
    PlaceInCenter(LabelConnect1     ,v[1][0]);
    PlaceInCenter(LabelConnectMic2  ,v[0][1]);
    PlaceInCenter(LabelConnect2     ,v[1][1]);
    PlaceInCenter(LabelConnectMaster,MergeRects(v[0][2],v[0][3]));
    PlaceInCenter(LabelConnectL     ,v[1][2]);
    PlaceInCenter(LabelConnectR     ,v[1][3]);
    PlaceInCenter(LabelConnectPower ,v[1][4]);
    //Connectors
    PlaceInCenter(ImageXlrFemaleMic1     ,v[2][0]);
    PlaceInCenter(ImageXlrFemaleMic2     ,v[2][1]);
    PlaceInCenter(ImageXlrMaleMasterLeft ,v[2][2]);
    PlaceInCenter(ImageXlrMaleMasterRight,v[2][3]);
    PlaceInCenter(ImageEuroMalePower     ,v[2][4]);
  }
}
//---------------------------------------------------------------------------





