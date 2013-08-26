//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitLightTable.h"
#include "UnitFormSimpleShine2.h"
#include "UnitVcl.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UnitFormMachine"
#pragma resource "*.dfm"
TFormSimpleShine2 *FormSimpleShine2;
//---------------------------------------------------------------------------
__fastcall TFormSimpleShine2::TFormSimpleShine2(TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
  mImageFaders(this->GetImageFaders()),
  mLabels(this->GetLabels()),
  mChannelFaders(24),
  mSimpleShine2(boost::shared_ptr<SimpleShine2>(new SimpleShine2))
{
  //Control
  for (int i=0; i!=24; ++i)
  {
    mChannelFaders[i] = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine2->mFaders[i],mImageFaders[i]));
  }
  mMasterFader = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine2->mFaderMaster,ImageFaderMaster));
  mCrossfaderA = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine2->mCrossfaderA,ImageCrossfaderA));
  mCrossfaderB = boost::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine2->mCrossfaderB,ImageCrossfaderB));
  //Connect
  mDmxFemaleOut = boost::shared_ptr<DmxFemaleControl>(
    new DmxFemaleControl(this,mSimpleShine2->mDmxFemaleOut,ImageDmxFemaleOut));
  mEuroMalePower = boost::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSimpleShine2->mEuroMalePower,ImageEuroMalePower));
  //Display
  mLedPower = boost::shared_ptr<LedControl>(new LedControl(
    mSimpleShine2->mLedPower,ImageLedPower));
  mLedA = boost::shared_ptr<LedControl>(new LedControl(
    mSimpleShine2->mLedA,ImageLedA));
  mLedB = boost::shared_ptr<LedControl>(new LedControl(
    mSimpleShine2->mLedB,ImageLedB));


  CreateWatermark(ImageView,ImageWatermark);
  OnResize(0);

  //Manually set the faders
  const int nFaders = mChannelFaders.size();
  for (int i=0; i!=nFaders; ++i)
  {
    mChannelFaders[i]->OnMouseDown(0,mImageFaders[i]->Height - 1);

  }
  mMasterFader->OnMouseDown(0,ImageFaderMaster->Height - 1);
  mCrossfaderA->OnMouseDown(0,ImageCrossfaderA->Height - 1);
  mCrossfaderB->OnMouseDown(0,ImageCrossfaderB->Height - 1);
}
//---------------------------------------------------------------------------
void TFormSimpleShine2::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      ImageBuffer->Canvas->Draw(0,0,ImageView->Picture->Graphic);
      break;
    case modeUse:
      //Update displays
      mLedPower->Update();
      mLedA->Update();
      mLedB->Update();
      //Start drawing
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer( mLabels);
      //Controllers
      DrawOnBuffer(mImageFaders);
      DrawOnBuffer(ImageCrossfaderA);
      DrawOnBuffer(ImageCrossfaderB);
      DrawOnBuffer(ImageFaderMaster);
      //Displays
      DrawOnBuffer(ImageLedPower);
      DrawOnBuffer(ImageLedA);
      DrawOnBuffer(ImageLedB);
      break;
    case modeConnect:
      ImageBuffer->Canvas->Draw(0,0,ImageWatermark->Picture->Graphic);
      //Labels
      DrawOnBuffer(LabelConnectPower);
      DrawOnBuffer(LabelConnectDmxOut);
      //Connects
      DrawOnBuffer(ImageEuroMalePower);
      DrawOnBuffer(ImageDmxFemaleOut);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormSimpleShine2::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      {
        const int nFaders = mImageFaders.size();
        for (int i=0; i!=nFaders; ++i)
        {
          TImage * const image = mImageFaders[i];
          if (OnImage(x,y,image))
          {
            mChannelFaders[i]->OnMouseDown(
              x - image->Left,
              y - image->Top);
            return;
          }

        }
      }
      if (OnImage(x,y,ImageFaderMaster))
      {
        mMasterFader->OnMouseDown(
          x - ImageFaderMaster->Left,
          y - ImageFaderMaster->Top);
      }
      else if (OnImage(x,y,ImageCrossfaderA))
      {
        mCrossfaderA->OnMouseDown(
          x - ImageCrossfaderA->Left,
          y - ImageCrossfaderA->Top);
      }
      else if (OnImage(x,y,ImageCrossfaderB))
      {
        mCrossfaderB->OnMouseDown(
          x - ImageCrossfaderB->Left,
          y - ImageCrossfaderB->Top);
      }


      break;
    case modeConnect:
      if (OnImage(x,y,ImageEuroMalePower))
        mFormParent->OnConnectorClick(mEuroMalePower.get());
      if (OnImage(x,y,ImageDmxFemaleOut))
        mFormParent->OnConnectorClick(mDmxFemaleOut.get());
      break;
    default: assert(!"Should not get here");
  }
}
//---------------------------------------------------------------------------
void TFormSimpleShine2::OnAfterResize()
{
  //Note: all indices in this function are y-x ordered
  //Use
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,20,12));
    //Resize bitmaps
    //Note: indices are y-x ordered
    SetSize(ImageFader1->Picture->Bitmap ,MergeRects(v[2][ 1],v[5][ 1]));
    SetSize(ImageFader2->Picture->Bitmap ,MergeRects(v[2][ 2],v[5][ 2]));
    SetSize(ImageFader3->Picture->Bitmap ,MergeRects(v[2][ 3],v[5][ 3]));
    SetSize(ImageFader4->Picture->Bitmap ,MergeRects(v[2][ 4],v[5][ 4]));
    SetSize(ImageFader5->Picture->Bitmap ,MergeRects(v[2][ 5],v[5][ 5]));
    SetSize(ImageFader6->Picture->Bitmap ,MergeRects(v[2][ 6],v[5][ 6]));
    SetSize(ImageFader7->Picture->Bitmap ,MergeRects(v[2][ 8],v[5][ 8]));
    SetSize(ImageFader8->Picture->Bitmap ,MergeRects(v[2][ 9],v[5][ 9]));
    SetSize(ImageFader9->Picture->Bitmap ,MergeRects(v[2][10],v[5][10]));
    SetSize(ImageFader10->Picture->Bitmap,MergeRects(v[2][11],v[5][11]));
    SetSize(ImageFader11->Picture->Bitmap,MergeRects(v[2][12],v[5][12]));
    SetSize(ImageFader12->Picture->Bitmap,MergeRects(v[2][13],v[5][13]));
    SetSize(ImageFader13->Picture->Bitmap,MergeRects(v[7][ 1],v[10][ 1]));
    SetSize(ImageFader14->Picture->Bitmap,MergeRects(v[7][ 2],v[10][ 2]));
    SetSize(ImageFader15->Picture->Bitmap,MergeRects(v[7][ 3],v[10][ 3]));
    SetSize(ImageFader16->Picture->Bitmap,MergeRects(v[7][ 4],v[10][ 4]));
    SetSize(ImageFader17->Picture->Bitmap,MergeRects(v[7][ 5],v[10][ 5]));
    SetSize(ImageFader18->Picture->Bitmap,MergeRects(v[7][ 6],v[10][ 6]));
    SetSize(ImageFader19->Picture->Bitmap,MergeRects(v[7][ 8],v[10][ 8]));
    SetSize(ImageFader20->Picture->Bitmap,MergeRects(v[7][ 9],v[10][ 9]));
    SetSize(ImageFader21->Picture->Bitmap,MergeRects(v[7][10],v[10][10]));
    SetSize(ImageFader22->Picture->Bitmap,MergeRects(v[7][11],v[10][11]));
    SetSize(ImageFader23->Picture->Bitmap,MergeRects(v[7][12],v[10][12]));
    SetSize(ImageFader24->Picture->Bitmap,MergeRects(v[7][13],v[10][13]));
    SetSize(ImageCrossfaderA->Picture->Bitmap,MergeRects(v[7][15],v[10][15]));
    SetSize(ImageCrossfaderB->Picture->Bitmap,MergeRects(v[7][16],v[10][16]));
    SetSize(ImageFaderMaster->Picture->Bitmap,MergeRects(v[7][18],v[10][18]));
    //Refresh all faders
    const int nFaders = mImageFaders.size();
    for (int i=0; i!=nFaders; ++i)
    {
      mImageFaders[i]->Refresh();
    }
    //Place bitmaps
    //Labels
    //Again y-x ordered indices
    PlaceInCenter( LabelUse1_1,v[ 1][ 1]);
    PlaceInCenter( LabelUse1_2,v[ 6][ 1]);
    PlaceInCenter( LabelUse1_3,v[11][ 1]);
    PlaceInCenter( LabelUse2_1,v[ 1][ 2]);
    PlaceInCenter( LabelUse2_2,v[ 6][ 2]);
    PlaceInCenter( LabelUse2_3,v[11][ 2]);
    PlaceInCenter( LabelUse3_1,v[ 1][ 3]);
    PlaceInCenter( LabelUse3_2,v[ 6][ 3]);
    PlaceInCenter( LabelUse3_3,v[11][ 3]);
    PlaceInCenter( LabelUse4_1,v[ 1][ 4]);
    PlaceInCenter( LabelUse4_2,v[ 6][ 4]);
    PlaceInCenter( LabelUse4_3,v[11][ 4]);
    PlaceInCenter( LabelUse5_1,v[ 1][ 5]);
    PlaceInCenter( LabelUse5_2,v[ 6][ 5]);
    PlaceInCenter( LabelUse5_3,v[11][ 5]);
    PlaceInCenter( LabelUse6_1,v[ 1][ 6]);
    PlaceInCenter( LabelUse6_2,v[ 6][ 6]);
    PlaceInCenter( LabelUse6_3,v[11][ 6]);
    PlaceInCenter( LabelUse7_1,v[ 1][ 8]);
    PlaceInCenter( LabelUse7_2,v[ 6][ 8]);
    PlaceInCenter( LabelUse7_3,v[11][ 8]);
    PlaceInCenter( LabelUse8_1,v[ 1][ 9]);
    PlaceInCenter( LabelUse8_2,v[ 6][ 9]);
    PlaceInCenter( LabelUse8_3,v[11][ 9]);
    PlaceInCenter( LabelUse9_1,v[ 1][10]);
    PlaceInCenter( LabelUse9_2,v[ 6][10]);
    PlaceInCenter( LabelUse9_3,v[11][10]);
    PlaceInCenter(LabelUse10_1,v[ 1][11]);
    PlaceInCenter(LabelUse10_2,v[ 6][11]);
    PlaceInCenter(LabelUse10_3,v[11][11]);
    PlaceInCenter(LabelUse11_1,v[ 1][12]);
    PlaceInCenter(LabelUse11_2,v[ 6][12]);
    PlaceInCenter(LabelUse11_3,v[11][12]);
    PlaceInCenter(LabelUse12_1,v[ 1][13]);
    PlaceInCenter(LabelUse12_2,v[ 6][13]);
    PlaceInCenter(LabelUse12_3,v[11][13]);
    PlaceInCenter(LabelUseCrossfader,MergeRects(v[6][14],v[6][17]));
    PlaceInCenter(LabelUseMaster,MergeRects(v[6][18],v[6][19]));
    PlaceInCenter(LabelUseSimpleShine2,MergeRects(v[2][14],v[5][18]));
    //Controls
    PlaceInCenter( ImageFader1,MergeRects(v[ 2][ 1],v[ 5][ 1]));
    PlaceInCenter( ImageFader2,MergeRects(v[ 2][ 2],v[ 5][ 2]));
    PlaceInCenter( ImageFader3,MergeRects(v[ 2][ 3],v[ 5][ 3]));
    PlaceInCenter( ImageFader4,MergeRects(v[ 2][ 4],v[ 5][ 4]));
    PlaceInCenter( ImageFader5,MergeRects(v[ 2][ 5],v[ 5][ 5]));
    PlaceInCenter( ImageFader6,MergeRects(v[ 2][ 6],v[ 5][ 6]));
    PlaceInCenter( ImageFader7,MergeRects(v[ 2][ 8],v[ 5][ 8]));
    PlaceInCenter( ImageFader8,MergeRects(v[ 2][ 9],v[ 5][ 9]));
    PlaceInCenter( ImageFader9,MergeRects(v[ 2][10],v[ 5][10]));
    PlaceInCenter(ImageFader10,MergeRects(v[ 2][11],v[ 5][11]));
    PlaceInCenter(ImageFader11,MergeRects(v[ 2][12],v[ 5][12]));
    PlaceInCenter(ImageFader12,MergeRects(v[ 2][13],v[ 5][13]));
    PlaceInCenter(ImageFader13,MergeRects(v[ 7][ 1],v[10][ 1]));
    PlaceInCenter(ImageFader14,MergeRects(v[ 7][ 2],v[10][ 2]));
    PlaceInCenter(ImageFader15,MergeRects(v[ 7][ 3],v[10][ 3]));
    PlaceInCenter(ImageFader16,MergeRects(v[ 7][ 4],v[10][ 4]));
    PlaceInCenter(ImageFader17,MergeRects(v[ 7][ 5],v[10][ 5]));
    PlaceInCenter(ImageFader18,MergeRects(v[ 7][ 6],v[10][ 6]));
    PlaceInCenter(ImageFader19,MergeRects(v[ 7][ 8],v[10][ 8]));
    PlaceInCenter(ImageFader20,MergeRects(v[ 7][ 9],v[10][ 9]));
    PlaceInCenter(ImageFader21,MergeRects(v[ 7][10],v[10][10]));
    PlaceInCenter(ImageFader22,MergeRects(v[ 7][11],v[10][11]));
    PlaceInCenter(ImageFader23,MergeRects(v[ 7][12],v[10][12]));
    PlaceInCenter(ImageFader24,MergeRects(v[ 7][13],v[10][13]));

    PlaceInCenter(ImageCrossfaderA,MergeRects(v[7][15],v[10][15]));
    PlaceInCenter(ImageCrossfaderB,MergeRects(v[7][16],v[10][16]));
    PlaceInCenter(ImageFaderMaster,MergeRects(v[7][18],v[10][19]));
    //Displays
    PlaceInCenter(ImageLedA,MergeRects(v[3][7],v[4][7]));
    PlaceInCenter(ImageLedB,MergeRects(v[8][7],v[9][7]));
    PlaceInCenter(ImageLedPower,v[1][18]);
  }
  //Connect
  {
    const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,2,2));
    //Labels
    PlaceInCenter(LabelConnectPower ,v[0][0]);
    PlaceInCenter(LabelConnectDmxOut,v[0][1]);
    //Connectors
    PlaceInCenter(ImageEuroMalePower,v[1][0]);
    PlaceInCenter(ImageDmxFemaleOut ,v[1][1]);
  }
}
//---------------------------------------------------------------------------
const std::vector<TImage*> TFormSimpleShine2::GetImageFaders() const
{
  //std::vector<TImage*> v(24,0);
  std::vector<TImage*> v(24);
  v[ 0] =  ImageFader1;
  v[ 1] =  ImageFader2;
  v[ 2] =  ImageFader3;
  v[ 3] =  ImageFader4;
  v[ 4] =  ImageFader5;
  v[ 5] =  ImageFader6;
  v[ 6] =  ImageFader7;
  v[ 7] =  ImageFader8;
  v[ 8] =  ImageFader9;
  v[ 9] = ImageFader10;
  v[10] = ImageFader11;
  v[11] = ImageFader12;
  v[12] = ImageFader13;
  v[13] = ImageFader14;
  v[14] = ImageFader15;
  v[15] = ImageFader16;
  v[16] = ImageFader17;
  v[17] = ImageFader18;
  v[18] = ImageFader19;
  v[19] = ImageFader20;
  v[20] = ImageFader21;
  v[21] = ImageFader22;
  v[22] = ImageFader23;
  v[23] = ImageFader24;
  return v;
}
//---------------------------------------------------------------------------
const std::vector<TImage*> TFormSimpleShine2::GetLabels() const
{
  //std::vector<TImage*> v(39,0);
  std::vector<TImage*> v(39);
  v[ 0] =  LabelUse1_1;
  v[ 1] =  LabelUse1_2;
  v[ 2] =  LabelUse1_3;
  v[ 3] =  LabelUse2_1;
  v[ 4] =  LabelUse2_2;
  v[ 5] =  LabelUse2_3;
  v[ 6] =  LabelUse3_1;
  v[ 7] =  LabelUse3_2;
  v[ 8] =  LabelUse3_3;
  v[ 9] =  LabelUse4_1;
  v[10] =  LabelUse4_2;
  v[11] =  LabelUse4_3;
  v[12] =  LabelUse5_1;
  v[13] =  LabelUse5_2;
  v[14] =  LabelUse5_3;
  v[15] =  LabelUse6_1;
  v[16] =  LabelUse6_2;
  v[17] =  LabelUse6_3;
  v[18] =  LabelUse7_1;
  v[19] =  LabelUse7_2;
  v[20] =  LabelUse7_3;
  v[21] =  LabelUse8_1;
  v[22] =  LabelUse8_2;
  v[23] =  LabelUse8_3;
  v[24] =  LabelUse9_1;
  v[25] =  LabelUse9_2;
  v[26] =  LabelUse9_3;
  v[27] =  LabelUse10_1;
  v[28] =  LabelUse10_2;
  v[29] =  LabelUse10_3;
  v[30] =  LabelUse11_1;
  v[31] =  LabelUse11_2;
  v[32] =  LabelUse11_3;
  v[33] =  LabelUse12_1;
  v[34] =  LabelUse12_2;
  v[35] =  LabelUse12_3;
  v[36] =  LabelUseCrossfader;
  v[37] =  LabelUseMaster;
  v[38] =  LabelUseSimpleShine2;
  return v;
}
//---------------------------------------------------------------------------






