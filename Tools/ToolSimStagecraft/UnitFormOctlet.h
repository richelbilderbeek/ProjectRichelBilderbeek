//---------------------------------------------------------------------------

#ifndef UnitFormOctletH
#define UnitFormOctletH
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
#include "UnitFormMachine.h"
//---------------------------------------------------------------------------
#include <vector>
#include "UnitFormMachine.h"
struct Octlet;
//struct ControllerControl;
struct ConnectorControl;
struct TwoSwitchControl;
struct Socket220Control;
struct Plug220Control;
struct TFormSimStagecraftMain;
//---------------------------------------------------------------------------
class TFormOctlet : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageSocket220_3;
  TImage *ImageTwoSwitchPower;
  TImage *ImageSocket220_2;
  TImage *ImageSocket220_1;
  TImage *ImagePlug220;
  TImage *ImageWatermark;
  TImage *ImageSocket220_4;
  TImage *ImageSocket220_5;
  TImage *ImageSocket220_6;
  TImage *ImageSocket220_7;
  TImage *ImageSocket220_8;
private:	// User declarations
  //Machine
  boost::shared_ptr<Octlet> mOctlet;
  //Control
  boost::shared_ptr<TwoSwitchControl> mTwoSwitchPower;
  //Connect
  std::vector<boost::shared_ptr<Socket220Control> > mSocket220Controls;
  boost::shared_ptr<Plug220Control> mPlug220;
  //Misc
  std::vector<TImage*> mImageSockets220;
  const std::vector<boost::shared_ptr<Socket220Control> >
    CreateSocket220Controls();

public:		// User declarations
  __fastcall TFormOctlet(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void UpdateBuffer();
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOctlet *FormOctlet;
//---------------------------------------------------------------------------
#endif
