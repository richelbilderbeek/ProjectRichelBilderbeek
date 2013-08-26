//---------------------------------------------------------------------------

#ifndef UnitFormSimpleSound1H
#define UnitFormSimpleSound1H
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
struct SimpleSound1;
//Control
struct FaderControl;
//Connect
struct EuroMaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class TFormSimpleSound1 : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageFaderMaster;
  TImage *ImageEuroMalePower;
  TImage *ImageXlrMaleMasterLeft;
  TImage *ImageXlrFemaleMic1;
  TImage *ImageXlrMaleMasterRight;
  TImage *ImageWatermark;
  TImage *ImageAudioSignal;
  TImage *ImageConnect1;
  TImage *ImageConnectMaster;
  TImage *ImageConnectMic;
  TImage *ImageConnectL;
  TImage *ImageConnectR;
  TImage *ImageConnectPower;
  TImage *LabelUseMaster;
  TImage *LabelUseSimpleSound1;
private:	// User declarations
  //Machine
  boost::shared_ptr<SimpleSound1> mSoundTable;
  //Control
  boost::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  boost::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  boost::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  __fastcall TFormSimpleSound1(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimpleSound1 *FormSimpleSound1;
//---------------------------------------------------------------------------
#endif
