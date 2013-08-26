//---------------------------------------------------------------------------

#ifndef UnitFormAlesisMultimix8H
#define UnitFormAlesisMultimix8H
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
class TFormAlesisMultimix8 : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageDialVolume1;
  TImage *ImageEuroMalePower;
  TImage *ImageXlrMaleMasterLeft;
  TImage *ImageXlrFemaleMic1;
  TImage *ImageXlrMaleMasterRight;
  TImage *ImageWatermark;
  TImage *ImageAudioSignal;
  TImage *ImageUse1;
  TImage *ImageConnect1;
  TImage *ImageConnectMaster;
  TImage *ImageConnectMic;
  TImage *ImageConnectL;
  TImage *ImageConnectR;
  TImage *ImageConnectPower;
  TImage *Image1;
  TImage *Image2;
  TImage *Image3;
  TImage *Image4;
  TImage *Image5;
  TImage *Image6;
  TImage *Image7;
  TImage *Image8;
  TImage *Image9;
  TImage *Image10;
  TImage *Image11;
  TImage *Image12;
  TImage *Image13;
  TImage *Image14;
  TImage *Image15;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TImage *Image16;
  TImage *Image17;
  TLabel *Label4;
  TLabel *Label5;
  TImage *Image18;
  TImage *Image19;
  TImage *Image20;
  TLabel *Label6;
  TLabel *Label7;
  TLabel *Label8;
  TLabel *Label9;
  TImage *Image21;
  TLabel *Label10;
  TLabel *Label11;
  TImage *Image22;
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
  __fastcall TFormAlesisMultimix8(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAlesisMultimix8 *FormAlesisMultimix8;
//---------------------------------------------------------------------------
#endif
