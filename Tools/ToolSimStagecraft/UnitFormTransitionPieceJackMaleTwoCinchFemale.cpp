//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitTransitionPiece.h"
#include "UnitVcl.h"
#include "UnitFormTransitionPieceJackMaleTwoCinchFemale.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTransitionPieceJackMaleTwoCinchFemale *FormTransitionPieceJackMaleTwoCinchFemale;
//---------------------------------------------------------------------------
__fastcall TFormTransitionPieceJackMaleTwoCinchFemale::TFormTransitionPieceJackMaleTwoCinchFemale(
    TComponent* Owner,
    TFormSimStagecraftMain * const formParent)
  : TFormMachine(Owner,formParent),
    mTransitionPiece(boost::shared_ptr<TransitionPieceJackMaleTwoCinchFemale>(
      new TransitionPieceJackMaleTwoCinchFemale))
{
  //Control
  //Connect
  mJack = boost::shared_ptr<JackMaleControl>(
    new JackMaleControl(this,mTransitionPiece->mJack,ImageJack));
  mCinchL = boost::shared_ptr<CinchWhiteFemaleControl>(
    new CinchWhiteFemaleControl(this,mTransitionPiece->mCinchL,ImageCinchL));
  mCinchR = boost::shared_ptr<CinchRedFemaleControl>(
    new CinchRedFemaleControl(this,mTransitionPiece->mCinchR,ImageCinchR));

  CreateWatermark(ImageView,ImageWatermark);

  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormTransitionPieceJackMaleTwoCinchFemale::UpdateBuffer()
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
      DrawOnBuffer(ImageJack);
      DrawOnBuffer(ImageCinchL);
      DrawOnBuffer(ImageCinchR);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void TFormTransitionPieceJackMaleTwoCinchFemale::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageJack)) mFormParent->OnConnectorClick(mJack.get());
      if (OnImage(x,y,ImageCinchL)) mFormParent->OnConnectorClick(mCinchL.get());
      if (OnImage(x,y,ImageCinchR)) mFormParent->OnConnectorClick(mCinchR.get());
      break;
  }
}
//---------------------------------------------------------------------------
void TFormTransitionPieceJackMaleTwoCinchFemale::OnAfterResize()
{
  const std::vector<std::vector<TRect> > v(GetRectsGrid(ClientRect,2,2));
  PlaceInCenter(ImageCinchL,v[0][0]);
  PlaceInCenter(ImageCinchR,v[1][0]);
  PlaceInCenter(ImageJack,  MergeRects(v[0][1],v[1][1]));
}
//---------------------------------------------------------------------------


