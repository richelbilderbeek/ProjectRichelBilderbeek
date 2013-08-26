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
#include "UnitFormRcfEvent3000.h"
#include "UnitFormMachine.h"
#include "UnitFormSprites.h"

#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormMachine"
#pragma resource "*.dfm"
TFormRcfEvent3000 *FormRcfEvent3000;
//---------------------------------------------------------------------------
__fastcall TFormRcfEvent3000::TFormRcfEvent3000(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSpeaker(boost::shared_ptr<RcfEvent3000>(new RcfEvent3000))
{
  //Control
  //Connect
  mInput = boost::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mSpeaker->mInput,ImageInput));
  mLink = boost::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mSpeaker->mLink,ImageLink));
  //Display


  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormRcfEvent3000::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update all
      DrawAudioSignal(ImageSound,mSpeaker->GetSoundLevel());
      //Start drawing
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      //Controls
      DrawOnBuffer(ImageSound);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      //Connectors
      DrawOnBuffer(ImageInput);
      DrawOnBuffer(ImageLink);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormRcfEvent3000::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageInput)) mFormParent->OnConnectorClick(mInput.get());
      if (OnImage(x,y,ImageLink )) mFormParent->OnConnectorClick(mLink.get() );
      break;
  }
}
//---------------------------------------------------------------------------
void TFormRcfEvent3000::OnAfterResize()
{
  //Use
  {
    //Get y-x-ordered vector of TRects
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,1,1));
    //Resize bitmaps
    //Place bitmaps
    //Labels
    //Controls
    //Displays
    PlaceInCenter(ImageSound,v[0][0]);
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,2,1));
    //Labels
    //Connectors
    PlaceInCenter(ImageInput,v[0][0]);
    PlaceInCenter(ImageLink ,v[0][1]);
  }
}
//---------------------------------------------------------------------------

