//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitDisplayControl.h"
#include "UnitMachine.h"
#include "UnitDimmerpack.h"
#include "UnitVcl.h"
#include "UnitFormDimblockV3.h"
#include "UnitFormSprites.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormMachine"
#pragma link "UnitFormMachine"
#pragma resource "*.dfm"
TFormDimblockV3 *FormDimblockV3;
//---------------------------------------------------------------------------
__fastcall TFormDimblockV3::TFormDimblockV3(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mDimblockV3(boost::shared_ptr<DimblockV3>(new DimblockV3))
{
  mImageSockets.push_back(ImageSocket1);
  mImageSockets.push_back(ImageSocket2);
  mImageSockets.push_back(ImageSocket3);
  mImageSockets.push_back(ImageSocket4);
  mImageSockets.push_back(ImageSocket5);
  mImageSockets.push_back(ImageSocket6);
  mImageSockets.push_back(ImageSocket7);
  mImageSockets.push_back(ImageSocket8);
  mImageSockets.push_back(ImageSocket9);
  mImageSockets.push_back(ImageSocket10);
  mImageSockets.push_back(ImageSocket11);
  mImageSockets.push_back(ImageSocket12);
  assert(mImageSockets.size() == 12);
  //Control
  //Connect
  mDmxMaleInput = boost::shared_ptr<DmxMaleControl>(new DmxMaleControl(this,
    mDimblockV3->mDmxMaleInput, ImageDmxMaleInput));
  mDmxFemaleThrough = boost::shared_ptr<DmxFemaleControl>(new DmxFemaleControl(this,
    mDimblockV3->mDmxFemaleOutput, ImageDmxFemaleThrough));
  mSocketPowerMale = boost::shared_ptr<SocketPowerMaleControl>(
    new SocketPowerMaleControl(this, mDimblockV3->mPowerMale, ImageSocketPowerMale));
  mSockets = this->CreateSocket220Controls();
  //Display
  mLedMainsPower = boost::shared_ptr<LedControl>(new LedControl(
    mDimblockV3->mLedMainsPower,ImageLedMainsPower));
  mLedNondimSet = boost::shared_ptr<LedControl>(new LedControl(
    mDimblockV3->mLedNondimSet,ImageLedNondimSet));
  mLedPresetSet = boost::shared_ptr<LedControl>(new LedControl(
    mDimblockV3->mLedPresetSet,ImageLedPresetSet));
  mLedDmxPresent = boost::shared_ptr<LedControl>(new LedControl(
    mDimblockV3->mLedDmxPresent,ImageLedDmxPresent));
  mLedWarning = boost::shared_ptr<LedControl>(new LedControl(
    mDimblockV3->mLedWarning,ImageLedWarning));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormDimblockV3::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update all
      mLedMainsPower->Update();
      mLedNondimSet->Update();
      mLedPresetSet->Update();
      mLedDmxPresent->Update();
      mLedWarning->Update();
      //Start drawing
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer(LabelUseMainsPower);
      DrawOnBuffer(LabelUseNondimSet);
      DrawOnBuffer(LabelUsePresetSet);
      DrawOnBuffer(LabelUseDmxPresent);
      DrawOnBuffer(LabelUseWarning);
      //Displays
      DrawOnBuffer(ImageLedMainsPower);
      DrawOnBuffer(ImageLedNondimSet);
      DrawOnBuffer(ImageLedPresetSet);
      DrawOnBuffer(ImageLedDmxPresent);
      DrawOnBuffer(ImageLedWarning);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer(LabelConnectDmxIn);
      DrawOnBuffer(LabelConnectDmxThrough);
      DrawOnBuffer(LabelConnectMains);
      DrawOnBuffer(LabelConnect1);
      DrawOnBuffer(LabelConnect2);
      DrawOnBuffer(LabelConnect3);
      DrawOnBuffer(LabelConnect4);
      DrawOnBuffer(LabelConnect5);
      DrawOnBuffer(LabelConnect6);
      DrawOnBuffer(LabelConnect7);
      DrawOnBuffer(LabelConnect8);
      DrawOnBuffer(LabelConnect9);
      DrawOnBuffer(LabelConnect10);
      DrawOnBuffer(LabelConnect11);
      DrawOnBuffer(LabelConnect12);
      //Connectors
      DrawOnBuffer(ImageDmxMaleInput);
      DrawOnBuffer(ImageDmxFemaleThrough);
      DrawOnBuffer(ImageSocketPowerMale);
      {
        const int nSockets = mSockets.size();
        for (int i=0; i!=nSockets; ++i)
        {
          DrawOnBuffer(mImageSockets[i]);
        }
      }
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormDimblockV3::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageDmxMaleInput))
        mFormParent->OnConnectorClick(mDmxMaleInput.get());
      if (OnImage(x,y,ImageDmxFemaleThrough))
        mFormParent->OnConnectorClick(mDmxFemaleThrough.get());
      if (OnImage(x,y,ImageSocketPowerMale))
        mFormParent->OnConnectorClick(mSocketPowerMale.get());
      {
        const int nSockets = mSockets.size();
        for (int i=0; i!=nSockets; ++i)
        {
          if (OnImage(x,y,mImageSockets[i]))
            mFormParent->OnConnectorClick(mSockets[i].get());

        }
      }
      break;
  }
}
//---------------------------------------------------------------------------
const std::vector<boost::shared_ptr<Socket220Control> >
  TFormDimblockV3::CreateSocket220Controls()
{
  std::vector<boost::shared_ptr<Socket220Control> > sockets;

  const int nSockets = mImageSockets.size();
  assert(mDimblockV3->mSockets.size() == mImageSockets.size() );

  for (int i=0; i!=nSockets; ++i)
  {
    boost::shared_ptr<Socket220Control> socket(new Socket220Control(
      this, mDimblockV3->mSockets[i], mImageSockets[i] ));
    sockets.push_back(socket);

  }

  assert(sockets.size() == 12);

  return sockets;
}
//---------------------------------------------------------------------------
void TFormDimblockV3::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,4,4));
    //Resize images
      //ImageFaderMaster->Picture->Bitmap->Height = MergeRects(v[1][0],v[3][0]).Height();
      //ImageFaderMaster->Refresh();
    //Labels
    PlaceInCenter(LabelUseMainsPower,v[0][0]);
    PlaceInCenter(LabelUseNondimSet ,v[0][1]);
    PlaceInCenter(LabelUsePresetSet ,v[0][2]);
    PlaceInCenter(LabelUseDmxPresent,v[0][3]);
    PlaceInCenter(LabelUseWarning   ,v[2][3]);
    //Diplay
    PlaceInCenter(ImageLedMainsPower,v[1][0]);
    PlaceInCenter(ImageLedNondimSet ,v[1][1]);
    PlaceInCenter(ImageLedPresetSet ,v[1][2]);
    PlaceInCenter(ImageLedDmxPresent,v[1][3]);
    PlaceInCenter(ImageLedWarning   ,v[3][3]);
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,9,5));
    //Labels
    PlaceInCenter(LabelConnectDmxIn,MergeRects(v[0][1],v[0][2]));
    PlaceInCenter(LabelConnectDmxThrough,MergeRects(v[1][1],v[1][2]));
    PlaceInCenter(LabelConnectMains,MergeRects(v[2][0],v[4][2]));
    PlaceInCenter(LabelConnect1,v[1][3]);
    PlaceInCenter(LabelConnect2,v[1][4]);
    PlaceInCenter(LabelConnect3,v[1][5]);
    PlaceInCenter(LabelConnect4,v[1][6]);
    PlaceInCenter(LabelConnect5,v[1][7]);
    PlaceInCenter(LabelConnect6,v[1][8]);
    PlaceInCenter(LabelConnect7,v[2][3]);
    PlaceInCenter(LabelConnect8,v[2][4]);
    PlaceInCenter(LabelConnect9,v[2][5]);
    PlaceInCenter(LabelConnect10,v[2][6]);
    PlaceInCenter(LabelConnect11,v[2][7]);
    PlaceInCenter(LabelConnect12,v[2][8]);
    //Connectors
    PlaceInCenter(ImageDmxMaleInput,v[0][0]);
    PlaceInCenter(ImageDmxFemaleThrough,v[1][0]);
    PlaceInCenter(ImageSocketPowerMale,v[2][1]);
    PlaceInCenter(ImageSocket1,v[0][3]);
    PlaceInCenter(ImageSocket2,v[0][4]);
    PlaceInCenter(ImageSocket3,v[0][5]);
    PlaceInCenter(ImageSocket4,v[0][6]);
    PlaceInCenter(ImageSocket5,v[0][7]);
    PlaceInCenter(ImageSocket6,v[0][8]);
    PlaceInCenter(ImageSocket7,v[3][3]);
    PlaceInCenter(ImageSocket8,v[3][4]);
    PlaceInCenter(ImageSocket9,v[3][5]);
    PlaceInCenter(ImageSocket10,v[3][6]);
    PlaceInCenter(ImageSocket11,v[3][7]);
    PlaceInCenter(ImageSocket12,v[3][8]);
  }
}
//---------------------------------------------------------------------------



