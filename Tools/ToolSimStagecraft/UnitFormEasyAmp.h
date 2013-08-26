//---------------------------------------------------------------------------

#ifndef UnitFormEasyAmpH
#define UnitFormEasyAmpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "UnitFormMachine.h"
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitFormMachine.h"
#include "UnitTapButtonControl.h"
//Machine
struct EasyAmp;
//Control
struct TwoSwitchControl;
struct DialControl;
//Connect
struct EuroMaleControl;
struct JackXlrFemaleControl;
struct SpeakonFemaleControl;
//Display
struct LedControl;
//---------------------------------------------------------------------------
class TFormEasyAmp : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
        TImage *ImageJackXlrR;
  TImage *ImageWatermark;
        TImage *ImageEuro;
        TImage *ImageJackXlrL;
  TTimer *TimerTick;
        TImage *ImagePowerSwitch;
        TImage *ImageGain;
        TImage *ImageSpeakonL;
        TImage *ImageSpeakonR;
        TImage *ImageLed;
private:	// User declarations
  //Machine
  boost::shared_ptr<EasyAmp> mAmplifier;
  //Control
  boost::shared_ptr<TwoSwitchControl> mPowerSwitch;
  boost::shared_ptr<DialControl> mGain;
  //Connect
  boost::shared_ptr<EuroMaleControl> mEuro;
  boost::shared_ptr<JackXlrFemaleControl> mJackXlrL;
  boost::shared_ptr<JackXlrFemaleControl> mJackXlrR;
  boost::shared_ptr<SpeakonFemaleControl> mSpeakonL;
  boost::shared_ptr<SpeakonFemaleControl> mSpeakonR;
  //Display
  boost::shared_ptr<LedControl> mLedPower;

public:		// User declarations
  __fastcall TFormEasyAmp(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEasyAmp *FormEasyAmp;
//---------------------------------------------------------------------------
#endif
