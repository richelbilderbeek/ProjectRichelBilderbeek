//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitFormCdPlayer.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitCdPlayer.h"
#include "UnitVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCdPlayer *FormCdPlayer;
//---------------------------------------------------------------------------
__fastcall TFormCdPlayer::TFormCdPlayer(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mCdPlayer(boost::shared_ptr<CdPlayer>(new CdPlayer))
{

  //Control
  mTapButtonPlay = boost::shared_ptr<TapButtonControl<CdPlayer> > (
    new TapButtonControl<CdPlayer>(this,mCdPlayer->mButtonPlay, ImageTapButtonPlay));
  mTapButtonStop = boost::shared_ptr<TapButtonControl<CdPlayer> > (
    new TapButtonControl<CdPlayer>(this,mCdPlayer->mButtonStop, ImageTapButtonStop));
  mTapButtonPower = boost::shared_ptr<TapButtonControl<CdPlayer> > (
    new TapButtonControl<CdPlayer>(this,mCdPlayer->mButtonPower, ImageTapButtonPower));

  //Connect
  mCinchFemaleOutL = boost::shared_ptr<CinchWhiteFemaleControl>(
    new CinchWhiteFemaleControl(this,mCdPlayer->mCinchFemaleOutL,ImageCinchFemaleOutL));
  mCinchFemaleOutR = boost::shared_ptr<CinchRedFemaleControl>(
    new CinchRedFemaleControl(this,mCdPlayer->mCinchFemaleOutR,ImageCinchFemaleOutR));
  mPlug220Power = boost::shared_ptr<Plug220Control>(
    new Plug220Control(this,mCdPlayer->mPlug220Power,ImagePlug220Power));
  //Display
  mAudioSignalDisplayL = boost::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mCdPlayer->mAudioSignalDisplayL,ImageAudioSignalL));
  mAudioSignalDisplayR = boost::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mCdPlayer->mAudioSignalDisplayR,ImageAudioSignalR));
  mLcdSymbolPlay = boost::shared_ptr<LcdSymbolPlayControl> (
    new LcdSymbolPlayControl(mCdPlayer->mLcdSymbolPlay,ImageLcdSymbolPlay));
  mLedPower = boost::shared_ptr<LedControl> (
    new LedControl(mCdPlayer->mLedPower,ImageLedPower));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormCdPlayer::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      //mCdPlayer->Tick(); //Important for recording and playing
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update displays
      //mCdPlayer->Tick(); //Important for recording and playing
      mAudioSignalDisplayL->Update();
      mAudioSignalDisplayR->Update();
      mLcdSymbolPlay->Update();
      mLedPower->Update();
      //Draw
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      //DrawOnBuffer(LabelUse1);
      //Controls
      DrawOnBuffer(ImageTapButtonPower);
      DrawOnBuffer(ImageTapButtonPlay);
      DrawOnBuffer(ImageTapButtonStop);
      //Display
      DrawOnBuffer(ImageLedPower);
      DrawOnBuffer(ImageLcdSymbolPlay);
      DrawOnBuffer(ImageAudioSignalL);
      DrawOnBuffer(ImageAudioSignalR);
      break;
    case modeConnect:
      //mCdPlayer->Tick(); //Important for recording and playing
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer(LabelConnectOut);
      //Connectors
      DrawOnBuffer(ImageCinchFemaleOutL);
      DrawOnBuffer(ImageCinchFemaleOutR);
      DrawOnBuffer(ImagePlug220Power);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormCdPlayer::OnMouseDown(const int x, const int y)
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
      else if (OnImage(x,y,ImageTapButtonStop))
      {
        mTapButtonStop->OnMouseDown(
          x - ImageTapButtonStop->Left,
          y - ImageTapButtonStop->Top);
      }
      break;
    case modeConnect:
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
void TFormCdPlayer::OnAfterResize()
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
    PlaceInCenter(ImageTapButtonPlay,v[0][3]);
    PlaceInCenter(ImageTapButtonStop,v[0][4]);
    //Others
    //Displays
    PlaceInCenter(ImageLedPower,v[0][0]);
    PlaceInCenter(ImageLcdSymbolPlay,v[0][6]);
    PlaceInCenter(ImageAudioSignalL,v[0][7]);
    PlaceInCenter(ImageAudioSignalR,v[0][8]);
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,5,2));
    //Labels
    PlaceInCenter(LabelConnectOut,MergeRects(v[0][2],v[0][3]));
    //Connectors
    PlaceInCenter(ImageCinchFemaleOutL,v[1][2]);
    PlaceInCenter(ImageCinchFemaleOutR,v[1][3]);
    PlaceInCenter(ImagePlug220Power   ,v[1][4]);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormCdPlayer::TimerTickTimer(TObject *Sender)
{
  mCdPlayer->Tick(); //Important for recording and playing
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------

