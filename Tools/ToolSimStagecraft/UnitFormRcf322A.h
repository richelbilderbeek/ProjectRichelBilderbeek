//---------------------------------------------------------------------------

#ifndef UnitFormRcf322AH
#define UnitFormRcf322AH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include "UnitFormMachine.h"
//---------------------------------------------------------------------------
#include <vector>
#include "UnitFormMachine.h"
//Machine
struct Rcf322A;
//Control
struct TwoSwitchControl;
struct DialControl;
//Connect
struct XlrMaleControl;
struct XlrFemaleControl;
struct JackFemaleControl;
struct EuroMaleControl;
//Display
struct LedControl;
//---------------------------------------------------------------------------
class TFormRcf322A : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageXlrFemale;
  TImage *ImageWatermark;
  TImage *ImageVolumeDial;
  TImage *ImageLedPower;
  TImage *ImageEuroMale;
  TImage *ImageXlrMale;
  TImage *ImageLedLimProt;
  TImage *ImageTwoSwitchPower;
  TImage *ImageSound;
  TImage *LabelUsePowerOn;
  TImage *LabelUseVolume;
  TImage *LabelUseLimProt;
  TImage *LabelConnectMains;
  TImage *LabelConnectBalanced;
  TImage *ImageJackFemale;
private:	// User declarations
  //Machine
  boost::shared_ptr<Rcf322A> mSpeaker;
  //Control
  boost::shared_ptr<TwoSwitchControl> mPowerSwitch;
  boost::shared_ptr<DialControl> mVolumeDial;
  //Connect
  boost::shared_ptr<EuroMaleControl> mEuroMale;
  boost::shared_ptr<XlrMaleControl> mXlrMale;
  boost::shared_ptr<XlrFemaleControl> mXlrFemale;
  boost::shared_ptr<JackFemaleControl> mJackFemale;
  //Display
  boost::shared_ptr<LedControl> mLedPower;
  boost::shared_ptr<LedControl> mLedLimProt;
public:		// User declarations
  __fastcall TFormRcf322A(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRcf322A *FormRcf322A;
//---------------------------------------------------------------------------
#endif
