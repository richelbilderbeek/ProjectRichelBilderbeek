//---------------------------------------------------------------------------

#ifndef UnitFormYamahaMG16_6FxH
#define UnitFormYamahaMG16_6FxH
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
struct SoundTableEasySound;
//Control
struct FaderControl;
//Connect
struct EuroMaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class TFormYamahaMg16_6Fx : public TFormMachine
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
  TImage *ImageUse1;
  TImage *ImageUseMaster;
  TImage *ImageConnect1;
  TImage *ImageConnectMaster;
  TImage *ImageConnectMic;
  TImage *ImageConnectL;
  TImage *ImageConnectR;
  TImage *ImageConnectPower;
  TImage *ImageFader2;
  TImage *ImageFader3;
  TImage *ImageFader4;
  TImage *ImageFader5;
  TImage *ImageFader6;
  TImage *Image6;
  TImage *Image7;
  TImage *Image8;
  TImage *Image9;
  TImage *Image10;
  TImage *Image11;
  TImage *Image12;
  TImage *Image13;
  TImage *ImageFaderGroup12;
  TImage *ImageFaderGroup34;
  TImage *Image1;
  TImage *Image2;
  TImage *Image3;
  TImage *Image4;
  TImage *Image5;
  TImage *Image14;
  TImage *Image15;
  TImage *Image16;
  TImage *Image17;
  TImage *Image18;
  TLabel *Label1;
  TLabel *Label2;
private:	// User declarations
  //Machine
  boost::shared_ptr<SoundTableEasySound> mSoundTable;
  //Control
  boost::shared_ptr<FaderControl> mFaderControl1;
  boost::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  boost::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  boost::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  boost::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  __fastcall TFormYamahaMg16_6Fx(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormYamahaMg16_6Fx *FormYamahaMg16_6Fx;
//---------------------------------------------------------------------------
#endif
