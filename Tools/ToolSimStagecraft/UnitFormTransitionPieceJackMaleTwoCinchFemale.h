//---------------------------------------------------------------------------

#ifndef UnitFormTransitionPieceJackMaleTwoCinchFemaleH
#define UnitFormTransitionPieceJackMaleTwoCinchFemaleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
//Machine
struct TransitionPieceJackMaleTwoCinchFemale;
//Connect
struct CinchWhiteFemaleControl;
struct CinchRedFemaleControl;
struct JackMaleControl;
//Misc
struct TFormSimStagecraftMain;
//---------------------------------------------------------------------------
class TFormTransitionPieceJackMaleTwoCinchFemale : public TFormMachine
{
__published:	// IDE-managed Components
  TImage *ImageView;
  TImage *ImageCinchL;
  TImage *ImageCinchR;
  TImage *ImageJack;
  TImage *ImageWatermark;
private:	// User declarations
  //Machine
  boost::shared_ptr<TransitionPieceJackMaleTwoCinchFemale> mTransitionPiece;
  //Control
  //Connect
  boost::shared_ptr<CinchWhiteFemaleControl> mCinchL;
  boost::shared_ptr<CinchRedFemaleControl> mCinchR;
  boost::shared_ptr<JackMaleControl> mJack;
public:		// User declarations
  __fastcall TFormTransitionPieceJackMaleTwoCinchFemale(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void UpdateBuffer();
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTransitionPieceJackMaleTwoCinchFemale *FormTransitionPieceJackMaleTwoCinchFemale;
//---------------------------------------------------------------------------
#endif
