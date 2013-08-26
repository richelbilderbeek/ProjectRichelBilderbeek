//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitMachine.h"
#include "UnitWallSocket220.h"
#include "UnitConnectorControl.h"
#include "UnitVcl.h"
#include "UnitFormWallSocket220.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormWallSocket220 *FormWallSocket220;
//---------------------------------------------------------------------------
__fastcall TFormWallSocket220::TFormWallSocket220(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mSocket220(boost::shared_ptr<WallSocket220>(new WallSocket220))
{
  mSocket220Control = boost::shared_ptr<Socket220Control>(
    new Socket220Control( this,mSocket220->mSocket220,ImageSocket220));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormWallSocket220::UpdateBuffer()
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
      DrawOnBuffer(ImageSocket220);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormWallSocket220::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageSocket220))
        mFormParent->OnConnectorClick(mSocket220Control.get());
      break;
    default: assert(!"Should not get here");
  }
}
//---------------------------------------------------------------------------
void TFormWallSocket220::OnAfterResize()
{
  PlaceInCenter(ImageSocket220,ClientRect);
}
//---------------------------------------------------------------------------


