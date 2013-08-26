//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitFormMdPlayer.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitMdPlayer.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMdPlayer *FormMdPlayer;
//---------------------------------------------------------------------------
__fastcall TFormMdPlayer::TFormMdPlayer(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mMdPlayer(boost::shared_ptr<MdPlayer>(new MdPlayer))
{

  //Control
  mTapButtonPlay = boost::shared_ptr<TapButtonControl<MdPlayer> > (
    new TapButtonControl<MdPlayer>(this,mMdPlayer->mButtonPlay, ImageTapButtonPlay));
  mTapButtonRecord = boost::shared_ptr<TapButtonControl<MdPlayer> > (
    new TapButtonControl<MdPlayer>(this,mMdPlayer->mButtonRecord, ImageTapButtonRecord));
  mTapButtonStop = boost::shared_ptr<TapButtonControl<MdPlayer> > (
    new TapButtonControl<MdPlayer>(this,mMdPlayer->mButtonStop, ImageTapButtonStop));
  mTapButtonPower = boost::shared_ptr<TapButtonControl<MdPlayer> > (
    new TapButtonControl<MdPlayer>(this,mMdPlayer->mButtonPower, ImageTapButtonPower));

  //Connect
  mCinchFemaleInL = boost::shared_ptr<CinchWhiteFemaleControl>(
    new CinchWhiteFemaleControl(this,mMdPlayer->mCinchFemaleInL,ImageCinchFemaleInL));
  mCinchFemaleInR = boost::shared_ptr<CinchRedFemaleControl>(
    new CinchRedFemaleControl(this,mMdPlayer->mCinchFemaleInR,ImageCinchFemaleInR));
  mCinchFemaleOutL = boost::shared_ptr<CinchWhiteFemaleControl>(
    new CinchWhiteFemaleControl(this,mMdPlayer->mCinchFemaleOutL,ImageCinchFemaleOutL));
  mCinchFemaleOutR = boost::shared_ptr<CinchRedFemaleControl>(
    new CinchRedFemaleControl(this,mMdPlayer->mCinchFemaleOutR,ImageCinchFemaleOutR));
  mPlug220Power = boost::shared_ptr<Plug220Control>(
    new Plug220Control(this,mMdPlayer->mPlug220Power,ImagePlug220Power));
  //Display
  mAudioSignalDisplayL = boost::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mMdPlayer->mAudioSignalDisplayL,ImageAudioSignalL));
  mAudioSignalDisplayR = boost::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mMdPlayer->mAudioSignalDisplayR,ImageAudioSignalR));
  mLcdSymbolRec = boost::shared_ptr<LcdSymbolRecControl> (
    new LcdSymbolRecControl(mMdPlayer->mLcdSymbolRecord,ImageLcdSymbolRec));
  mLcdSymbolPlay = boost::shared_ptr<LcdSymbolPlayControl> (
    new LcdSymbolPlayControl(mMdPlayer->mLcdSymbolPlay,ImageLcdSymbolPlay));
  mLedPower = boost::shared_ptr<LedControl> (
    new LedControl(mMdPlayer->mLedPower,ImageLedPower));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormMdPlayer::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      mMdPlayer->Tick(); //Important for recording and playing
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update displays
      mMdPlayer->Tick(); //Important for recording and playing
      mAudioSignalDisplayL->Update();
      mAudioSignalDisplayR->Update();
      mLcdSymbolRec->Update();
      mLcdSymbolPlay->Update();
      mLedPower->Update();
      //Draw
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      //DrawOnBuffer(LabelUse1);
      //Controls
      DrawOnBuffer(ImageTapButtonPower);
      DrawOnBuffer(ImageTapButtonRecord);
      DrawOnBuffer(ImageTapButtonPlay);
      DrawOnBuffer(ImageTapButtonStop);
      //Display
      DrawOnBuffer(ImageLedPower);
      DrawOnBuffer(ImageLcdSymbolRec);
      DrawOnBuffer(ImageLcdSymbolPlay);
      DrawOnBuffer(ImageAudioSignalL);
      DrawOnBuffer(ImageAudioSignalR);
      break;
    case modeConnect:
      mMdPlayer->Tick(); //Important for recording and playing
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer(LabelConnectIn);
      DrawOnBuffer(LabelConnectOut);
      //Connectors
      DrawOnBuffer(ImageCinchFemaleInL);
      DrawOnBuffer(ImageCinchFemaleInR);
      DrawOnBuffer(ImageCinchFemaleOutL);
      DrawOnBuffer(ImageCinchFemaleOutR);
      DrawOnBuffer(ImagePlug220Power);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormMdPlayer::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageTapButtonPower))
      {
        mTapButtonPower->OnMouseDown(
          x - ImageTapButtonPower->Left,
          y - ImageTapButtonPower->Top);
      }
      else if (OnImage(x,y,ImageTapButtonPlay))
      {
        mTapButtonPlay->OnMouseDown(
          x - ImageTapButtonPlay->Left,
          y - ImageTapButtonPlay->Top);
      }
      else if (OnImage(x,y,ImageTapButtonRecord))
      {
        mTapButtonRecord->OnMouseDown(
          x - ImageTapButtonRecord->Left,
          y - ImageTapButtonRecord->Top);
      }
      else if (OnImage(x,y,ImageTapButtonStop))
      {
        mTapButtonStop->OnMouseDown(
          x - ImageTapButtonStop->Left,
          y - ImageTapButtonStop->Top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageCinchFemaleInL))
        mFormParent->OnConnectorClick(mCinchFemaleInL.get());
      if (OnImage(x,y,ImageCinchFemaleInR))
        mFormParent->OnConnectorClick(mCinchFemaleInR.get());
      if (OnImage(x,y,ImageCinchFemaleOutL))
        mFormParent->OnConnectorClick(mCinchFemaleOutL.get());
      if (OnImage(x,y,ImageCinchFemaleOutR))
        mFormParent->OnConnectorClick(mCinchFemaleOutR.get());
      if (OnImage(x,y,ImagePlug220Power))
        mFormParent->OnConnectorClick(mPlug220Power.get());
      break;
  }
}
//---------------------------------------------------------------------------
void TFormMdPlayer::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,9,1));
    //Resize bitmaps
    //ImageFader1->Picture->Bitmap->Height = MergeRects(v[4][2],v[6][2]).Height();
    //ImageFader1->Refresh();
    //Place bitmaps
    //Labels
    //Controls
    PlaceInCenter(ImageTapButtonPower,v[0][1]);
    PlaceInCenter(ImageTapButtonRecord,v[0][2]);
    PlaceInCenter(ImageTapButtonPlay,v[0][3]);
    PlaceInCenter(ImageTapButtonStop,v[0][4]);
    //Others
    //Displays
    PlaceInCenter(ImageLedPower,v[0][0]);
    PlaceInCenter(ImageLcdSymbolRec,v[0][5]);
    PlaceInCenter(ImageLcdSymbolPlay,v[0][6]);
    PlaceInCenter(ImageAudioSignalL,v[0][7]);
    PlaceInCenter(ImageAudioSignalR,v[0][8]);
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,5,2));
    //Labels
    PlaceInCenter(LabelConnectIn ,MergeRects(v[0][0],v[0][1]));
    PlaceInCenter(LabelConnectOut,MergeRects(v[0][2],v[0][3]));
    //Connectors
    PlaceInCenter(ImageCinchFemaleInL ,v[1][0]);
    PlaceInCenter(ImageCinchFemaleInR ,v[1][1]);
    PlaceInCenter(ImageCinchFemaleOutL,v[1][2]);
    PlaceInCenter(ImageCinchFemaleOutR,v[1][3]);
    PlaceInCenter(ImagePlug220Power   ,v[1][4]);
  }
}
//---------------------------------------------------------------------------






