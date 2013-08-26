//---------------------------------------------------------------------------

#ifndef UnitFormSimpleSound4H
#define UnitFormSimpleSound4H
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
struct SimpleSound4;
//Control
struct FaderControl;
struct DialControl;
struct PressButtonControl;
//Connect
struct CinchRedFemaleControl;
struct CinchWhiteFemaleControl;
struct EuroMaleControl;
struct JackFemaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class TFormSimpleSound4 : public TFormMachine
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
  TImage *ImagePressButtonPfl1;
  TImage *ImagePressButtonPfl2;
  TImage *ImageDialGain1;
  TImage *ImageDialGain2;
  TImage *LabelUseGain;
  TImage *LabelUsePfl;
  TImage *LabelUseSimpleSound4;
  TImage *LabelUseAux1;
  TImage *ImageDialAux1_1;
  TImage *ImageDialAux1_2;
  TImage *LabelUseSend;
  TImage *ImageDialSendAux1;
  TImage *ImageJackFemaleAux1;
  TImage *LabelConnectAux1;
  TImage *ImageFader3;
  TImage *ImagePressButtonPfl3;
  TImage *ImageDialAux1_3;
  TImage *ImageDialGain3;
  TImage *LabelUse3;
  TImage *ImageXlrFemaleMic3;
  TImage *LabelConnect3;
  TImage *LabelConnectMic3;
  TImage *Image1;
  TImage *Image2;
  TImage *Image3;
  TImage *ImageDialAux1_4;
  TImage *ImagePressButtonPfl4;
  TImage *ImageFader4;
  TImage *LabelUseAux2;
  TImage *ImageDialAux2_1;
  TImage *ImageDialAux2_2;
  TImage *ImageDialAux2_3;
  TImage *ImageDialAux2_4;
  TImage *ImageDialSendAux2;
  TImage *LabelUse4;
  TImage *ImageJackFemaleAux2;
  TImage *LabelConnectAux2;
  TImage *LabelConnect4;
  TImage *ImageCinchFemaleWhite4;
  TImage *ImageCinchFemaleRed4;
private:	// User declarations
  //Machine
  boost::shared_ptr<SimpleSound4> mSoundTable;
  //Control
  boost::shared_ptr<FaderControl> mFaderControl1;
  boost::shared_ptr<FaderControl> mFaderControl2;
  boost::shared_ptr<FaderControl> mFaderControl3;
  boost::shared_ptr<FaderControl> mFaderControl4;
  boost::shared_ptr<DialControl> mDialControlGain1;
  boost::shared_ptr<DialControl> mDialControlGain2;
  boost::shared_ptr<DialControl> mDialControlGain3;
  boost::shared_ptr<DialControl> mDialControlAux1_1;
  boost::shared_ptr<DialControl> mDialControlAux1_2;
  boost::shared_ptr<DialControl> mDialControlAux1_3;
  boost::shared_ptr<DialControl> mDialControlAux1_4;
  boost::shared_ptr<DialControl> mDialControlAux2_1;
  boost::shared_ptr<DialControl> mDialControlAux2_2;
  boost::shared_ptr<DialControl> mDialControlAux2_3;
  boost::shared_ptr<DialControl> mDialControlAux2_4;
  boost::shared_ptr<DialControl> mDialControlSendAux1;
  boost::shared_ptr<DialControl> mDialControlSendAux2;
  boost::shared_ptr<PressButtonControl> mPressButtonControlPfl1;
  boost::shared_ptr<PressButtonControl> mPressButtonControlPfl2;
  boost::shared_ptr<PressButtonControl> mPressButtonControlPfl3;
  boost::shared_ptr<PressButtonControl> mPressButtonControlPfl4;
  boost::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  boost::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  boost::shared_ptr<XlrFemaleControl> mXlrFemaleMic2;
  boost::shared_ptr<XlrFemaleControl> mXlrFemaleMic3;
  boost::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleL4;
  boost::shared_ptr<CinchRedFemaleControl> mCinchFemaleR4;
  boost::shared_ptr<JackFemaleControl> mJackFemaleAux1;
  boost::shared_ptr<JackFemaleControl> mJackFemaleAux2;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  boost::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  __fastcall TFormSimpleSound4(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimpleSound4 *FormSimpleSound4;
//---------------------------------------------------------------------------
#endif
