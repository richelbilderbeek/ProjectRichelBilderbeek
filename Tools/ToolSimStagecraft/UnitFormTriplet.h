//---------------------------------------------------------------------------

#ifndef UnitFormTripletH
#define UnitFormTripletH
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
struct Triplet;
//struct ControllerControl;
struct ConnectorControl;
struct TwoSwitchControl;
struct Socket220Control;
struct Plug220Control;
struct TFormSimStagecraftMain;
//---------------------------------------------------------------------------
class TFormTriplet : public TFormMachine
{
__published:	// IDE-managed Components
  TImage *ImageView;
  TImage *ImageSocket220_3;
  TImage *ImageSocket220_2;
  TImage *ImageSocket220_1;
  TImage *ImagePlug220;
  TImage *ImageWatermark;
private:	// User declarations
  //Machine
  boost::shared_ptr<Triplet> mTriplet;
  //Control
  //Connect
  boost::shared_ptr<Socket220Control> mSocket220_1;
  boost::shared_ptr<Socket220Control> mSocket220_2;
  boost::shared_ptr<Socket220Control> mSocket220_3;
  boost::shared_ptr<Plug220Control> mPlug220;
public:		// User declarations
  __fastcall TFormTriplet(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void UpdateBuffer();
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTriplet *FormTriplet;
//---------------------------------------------------------------------------
#endif
