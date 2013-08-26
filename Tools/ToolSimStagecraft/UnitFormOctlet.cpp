//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitOctlet.h"
#include "UnitVcl.h"
#include "UnitFormOctlet.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormMachine"
#pragma resource "*.dfm"
TFormOctlet *FormOctlet;
//---------------------------------------------------------------------------
__fastcall TFormOctlet::TFormOctlet(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mOctlet(boost::shared_ptr<Octlet>(new Octlet))
{
  mImageSockets220.push_back(ImageSocket220_1);
  mImageSockets220.push_back(ImageSocket220_2);
  mImageSockets220.push_back(ImageSocket220_3);
  mImageSockets220.push_back(ImageSocket220_4);
  mImageSockets220.push_back(ImageSocket220_5);
  mImageSockets220.push_back(ImageSocket220_6);
  mImageSockets220.push_back(ImageSocket220_7);
  mImageSockets220.push_back(ImageSocket220_8);
  assert(mImageSockets220.size() == 8);


  //Control
  mTwoSwitchPower = boost::shared_ptr<TwoSwitchControl>(
    new TwoSwitchControl(this,mOctlet->mPowerSwitch,ImageTwoSwitchPower));
  //Connect
  mPlug220 = boost::shared_ptr<Plug220Control>(
    new Plug220Control(this,mOctlet->mPlug,ImagePlug220));
  mSocket220Controls = this->CreateSocket220Controls();

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);

  //Turn power off by default
  mTwoSwitchPower->OnMouseDown(0,0); //Top of powerswitch turns off
}
//---------------------------------------------------------------------------
void TFormOctlet::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImageTwoSwitchPower);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      DrawOnBuffer(ImagePlug220);
      {
        const int nSockets = mSocket220Controls.size();
        for (int i=0; i!=nSockets; ++i)
        {
          DrawOnBuffer(mImageSockets220[i]);
        }
      }
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormOctlet::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageTwoSwitchPower))
      {
        mTwoSwitchPower->OnMouseDown(
          x - ImageTwoSwitchPower->Left,
          y - ImageTwoSwitchPower->Top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImagePlug220)) mFormParent->OnConnectorClick(mPlug220.get());
      {
        const int nSockets = mSocket220Controls.size();
        for (int i=0; i!=nSockets; ++i)
        {
          if (OnImage(x,y,mImageSockets220[i]))
            mFormParent->OnConnectorClick(mSocket220Controls[i].get());

        }
      }
      break;
  }
}
//---------------------------------------------------------------------------
void TFormOctlet::OnAfterResize()
{
  const std::vector<TRect> v(GetRectsHorizontal(ClientRect,5));
  const std::vector<TRect> v0(GetRectsVertical(v[0],2));
  const std::vector<TRect> v1(GetRectsVertical(v[1],2));
  const std::vector<TRect> v2(GetRectsVertical(v[2],2));
  const std::vector<TRect> v3(GetRectsVertical(v[3],2));
  PlaceInCenter(mImageSockets220[0],v0[0]);
  PlaceInCenter(mImageSockets220[1],v1[0]);
  PlaceInCenter(mImageSockets220[2],v2[0]);
  PlaceInCenter(mImageSockets220[3],v3[0]);
  PlaceInCenter(mImageSockets220[4],v0[1]);
  PlaceInCenter(mImageSockets220[5],v1[1]);
  PlaceInCenter(mImageSockets220[6],v2[1]);
  PlaceInCenter(mImageSockets220[7],v3[1]);
  PlaceInCenter(ImagePlug220    ,v[4]);

  PlaceInCenter(ImageTwoSwitchPower,ClientRect);
}
//---------------------------------------------------------------------------
const std::vector<boost::shared_ptr<Socket220Control> >
  TFormOctlet::CreateSocket220Controls()
{
  std::vector<boost::shared_ptr<Socket220Control> > sockets;

  const int nSockets = mImageSockets220.size();
  assert(mOctlet->mSockets220.size() == mImageSockets220.size() );

  for (int i=0; i!=nSockets; ++i)
  {
    boost::shared_ptr<Socket220Control> socket(new Socket220Control(
      this, mOctlet->mSockets220[i], mImageSockets220[i] ));
    sockets.push_back(socket);

  }

  assert(sockets.size() == 8);

  return sockets;
}
//---------------------------------------------------------------------------


