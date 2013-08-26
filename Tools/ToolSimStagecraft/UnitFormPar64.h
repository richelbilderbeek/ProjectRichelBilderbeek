//---------------------------------------------------------------------------

#ifndef UnitFormPar64H
#define UnitFormPar64H
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
struct Par64;
struct Plug220Control;
struct TFormSimStagecraftMain;
//---------------------------------------------------------------------------
class TFormPar64 : public TFormMachine
{
__published:	// IDE-managed Components
  TImage *ImageView;
  TImage *ImagePlug220;
  TImage *ImageLamp;
  TImage *ImageWatermark;
private:	// User declarations
  //Machine
  boost::shared_ptr<Par64> mPar64;
  //Control
  //Connect
  boost::shared_ptr<Plug220Control> mPlug220;
public:		// User declarations
  __fastcall TFormPar64(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  const TImage * const GetImageBuffer() const;
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPar64 *FormPar64;
//---------------------------------------------------------------------------
#endif
