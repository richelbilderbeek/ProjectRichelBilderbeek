//---------------------------------------------------------------------------

#ifndef UnitFormTorqueTm200PH
#define UnitFormTorqueTm200PH
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
struct SpeakerRcf322A;
//Control
struct TwoSwitchControl;
struct DialControl;
//Connect
struct XlrMaleControl;
struct XlrFemaleControl;
struct EuroMaleControl;
//Display
struct LedControl;
//---------------------------------------------------------------------------
class TFormTorqueTm200P : public TFormMachine
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
  TLabel *LabelPower;
  TImage *ImageLedPower;
  TImage *ImageEuroMale;
  TImage *ImageXlrMale;
  TImage *ImagePowerSwitch;
  TLabel *LabelVolume;
  TImage *ImageSound;
private:	// User declarations
  //Machine
  boost::shared_ptr<SpeakerRcf322A> mSpeaker;
  //Control
  boost::shared_ptr<TwoSwitchControl> mPowerSwitch;
  boost::shared_ptr<DialControl> mVolumeDial;
  //Connect
  boost::shared_ptr<EuroMaleControl> mEuroMale;
  boost::shared_ptr<XlrMaleControl> mXlrMale;
  boost::shared_ptr<XlrFemaleControl> mXlrFemale;
  //Display
  boost::shared_ptr<LedControl> mLedPower;
  boost::shared_ptr<LedControl> mLedLimProt;
public:		// User declarations
  __fastcall TFormTorqueTm200P(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  const TImage * const GetImageBuffer() const;
  const Machine * const GetMachine() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTorqueTm200P *FormTorqueTm200P;
//---------------------------------------------------------------------------
#endif
