//---------------------------------------------------------------------------

#ifndef UnitFormSimpleSound2H
#define UnitFormSimpleSound2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
//Machine
struct SimpleSound2;
//Control
struct FaderControl;
struct DialControl;
struct PressButtonControl;
//Connect
struct EuroMaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class TFormSimpleSound2 : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageFader1;
  TImage *ImageFaderMaster;
  TImage *ImageEuroMalePower;
  TImage *ImageXlrMaleMasterLeft;
  TImage *ImageXlrFemaleMic1;
  TImage *ImageXlrMaleMasterRight;
  TImage *ImageWatermark;
  TImage *ImageAudioSignal;
  TImage *LabelUseMaster;
  TImage *LabelConnect1;
  TImage *LabelConnectMaster;
  TImage *LabelConnectMic1;
  TImage *LabelConnectL;
  TImage *LabelConnectR;
  TImage *LabelConnectPower;
  TImage *ImageFader2;
  TImage *LabelUse2;
  TImage *LabelUse1;
  TImage *ImageXlrFemaleMic2;
  TImage *LabelConnectMic2;
  TImage *LabelConnect2;
  TImage *ImagePressButton1;
  TImage *ImagePressButton2;
  TImage *ImageDial1;
  TImage *ImageDial2;
  TImage *LabelUseGain;
  TImage *LabelUsePfl;
  TImage *LabelUseSimpleSound2;
private:	// User declarations
  //Machine
  boost::shared_ptr<SimpleSound2> mSoundTable;
  //Control
  boost::shared_ptr<FaderControl> mFaderControl1;
  boost::shared_ptr<FaderControl> mFaderControl2;
  boost::shared_ptr<DialControl> mDialControl1;
  boost::shared_ptr<DialControl> mDialControl2;
  boost::shared_ptr<PressButtonControl> mPressButtonControl1;
  boost::shared_ptr<PressButtonControl> mPressButtonControl2;
  boost::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  boost::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  boost::shared_ptr<XlrFemaleControl> mXlrFemaleMic2;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  boost::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  __fastcall TFormSimpleSound2(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimpleSound2 *FormSimpleSound2;
//---------------------------------------------------------------------------
#endif
