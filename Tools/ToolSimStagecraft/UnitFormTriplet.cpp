//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitTriplet.h"
#include "UnitVcl.h"
#include "UnitFormTriplet.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTriplet *FormTriplet;
//---------------------------------------------------------------------------
__fastcall TFormTriplet::TFormTriplet(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mTriplet(boost::shared_ptr<Triplet>(new Triplet))
{

  //Control
  //Connect
  mSocket220_1 = boost::shared_ptr<Socket220Control>(
    new Socket220Control(this,mTriplet->mSocket220_1,ImageSocket220_1));
  mSocket220_2 = boost::shared_ptr<Socket220Control>(
    new Socket220Control(this,mTriplet->mSocket220_2,ImageSocket220_2));
  mSocket220_3 = boost::shared_ptr<Socket220Control>(
    new Socket220Control(this,mTriplet->mSocket220_3,ImageSocket220_3));
  mPlug220 = boost::shared_ptr<Plug220Control>(
    new Plug220Control(this,mTriplet->mPlug,ImagePlug220));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormTriplet::UpdateBuffer()
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
      DrawOnBuffer(ImageSocket220_1);
      DrawOnBuffer(ImageSocket220_2);
      DrawOnBuffer(ImageSocket220_3);
      DrawOnBuffer(ImagePlug220);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormTriplet::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageSocket220_1)) mFormParent->OnConnectorClick(mSocket220_1.get());
      if (OnImage(x,y,ImageSocket220_2)) mFormParent->OnConnectorClick(mSocket220_2.get());
      if (OnImage(x,y,ImageSocket220_3)) mFormParent->OnConnectorClick(mSocket220_3.get());
      if (OnImage(x,y,ImagePlug220)) mFormParent->OnConnectorClick(mPlug220.get());
      break;
  }
}
//---------------------------------------------------------------------------
void TFormTriplet::OnAfterResize()
{
  const std::vector<TRect> v(GetRectsHorizontal(ClientRect,4));
  PlaceInCenter(ImageSocket220_1,v[0]);
  PlaceInCenter(ImageSocket220_2,v[1]);
  PlaceInCenter(ImageSocket220_3,v[2]);
  PlaceInCenter(ImagePlug220    ,v[3]);
}
//---------------------------------------------------------------------------


