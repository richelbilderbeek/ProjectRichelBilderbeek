//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitMachine.h"
#include "UnitWallSocketPower.h"
#include "UnitConnectorControl.h"
#include "UnitVcl.h"
#include "UnitFormWallSocketPower.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormWallSocketPower *FormWallSocketPower;
//---------------------------------------------------------------------------
__fastcall TFormWallSocketPower::TFormWallSocketPower(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSocketPower(boost::shared_ptr<WallSocketPower>(new WallSocketPower))
{
  //Connect
  mSocketPowerControl = boost::shared_ptr<SocketPowerFemaleControl>(
    new SocketPowerFemaleControl( this,mSocketPower->mSocketPower,ImageSocketPower));


  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormWallSocketPower::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageSocketPower);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormWallSocketPower::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageSocketPower))
        mFormParent->OnConnectorClick(mSocketPowerControl.get());
      break;
    default: assert(!"Should not get here");
  }
}
//---------------------------------------------------------------------------
void TFormWallSocketPower::OnAfterResize()
{
  PlaceInCenter(ImageSocketPower,ClientRect);
}
//---------------------------------------------------------------------------

