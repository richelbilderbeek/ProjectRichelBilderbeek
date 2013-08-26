//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitLamp.h"
#include "UnitVcl.h"
#include "UnitFormPar64.h"
#include "UnitFormMachine.h"
#include "UnitFormSprites.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPar64 *FormPar64;
//---------------------------------------------------------------------------
__fastcall TFormPar64::TFormPar64(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mPar64(boost::shared_ptr<Par64>(new Par64))
{
  //Control
  //Connect
  mPlug220 = boost::shared_ptr<Plug220Control>(
    new Plug220Control(this,mPar64->mPlug220,ImagePlug220));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormPar64::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update images
      DrawLamp(ImageLamp,mPar64->GetLightIntensity(),255,255,0);
      //Update buffer
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageLamp);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImagePlug220);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
  //Drawing is done by TFormSimStagecraftMain
}
//---------------------------------------------------------------------------
void TFormPar64::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImagePlug220))
      {
        mFormParent->OnConnectorClick(mPlug220.get());
      }
      break;
  }
}
//---------------------------------------------------------------------------
void TFormPar64::OnAfterResize()
{
  PlaceInCenter(ImageLamp,ClientRect);
  PlaceInCenter(ImagePlug220,ClientRect);
}
//---------------------------------------------------------------------------

