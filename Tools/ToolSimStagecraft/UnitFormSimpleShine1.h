//---------------------------------------------------------------------------

#ifndef UnitFormSimpleShine1H
#define UnitFormSimpleShine1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
//#include "UnitEnumMachineType.h"
#include "UnitFormMachine.h"
struct FaderControl;
struct SimpleShine1;
struct DmxFemaleControl;
struct EuroMaleControl;
//---------------------------------------------------------------------------
class TFormSimpleShine1 : public TFormMachine
{
__published:	// IDE-managed Components
  TImage *ImageView;
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageFaderMaster;
  TImage *ImageFader1;
  TImage *ImageEuroMalePower;
  TImage *ImageDmxFemaleOut;
  TImage *ImageWatermark;
  TImage *LabelUse1;
  TImage *LabelUseMaster;
  TImage *LabelUse2;
  TImage *ImageFader2;
  TImage *ImageFader3;
  TImage *ImageFader4;
  TImage *ImageFader5;
  TImage *ImageFader6;
  TImage *LabelUse3;
  TImage *LabelUse4;
  TImage *LabelUse5;
  TImage *LabelUse6;
  TImage *ImageFader7;
  TImage *LabelUse7;
  TImage *ImageFader8;
  TImage *LabelUse8;
  TImage *ImageFader9;
  TImage *LabelUse9;
  TImage *LabelUse10;
  TImage *ImageFader10;
  TImage *ImageFader11;
  TImage *LabelUse11;
  TImage *LabelUse12;
  TImage *ImageFader12;
  TImage *LabelConnectPower;
  TImage *LabelConnectDmxOut;
  TImage *LabelUseSimpleShine1;
  TImage *ImageLedPower;
private:	// User declarations
  //Machine
  boost::shared_ptr<SimpleShine1> mSimpleShine1;
  //Control
  boost::shared_ptr<FaderControl> mFaderControl1;
  boost::shared_ptr<FaderControl> mFaderControl2;
  boost::shared_ptr<FaderControl> mFaderControl3;
  boost::shared_ptr<FaderControl> mFaderControl4;
  boost::shared_ptr<FaderControl> mFaderControl5;
  boost::shared_ptr<FaderControl> mFaderControl6;
  boost::shared_ptr<FaderControl> mFaderControl7;
  boost::shared_ptr<FaderControl> mFaderControl8;
  boost::shared_ptr<FaderControl> mFaderControl9;
  boost::shared_ptr<FaderControl> mFaderControl10;
  boost::shared_ptr<FaderControl> mFaderControl11;
  boost::shared_ptr<FaderControl> mFaderControl12;
  boost::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  boost::shared_ptr<DmxFemaleControl> mDmxFemaleOut;
  boost::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  boost::shared_ptr<LedControl> mLedControlPower;
public:		// User declarations
  __fastcall TFormSimpleShine1(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  const TImage * const GetImageBuffer() const;
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();

};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimpleShine1 *FormSimpleShine1;
//---------------------------------------------------------------------------
#endif
