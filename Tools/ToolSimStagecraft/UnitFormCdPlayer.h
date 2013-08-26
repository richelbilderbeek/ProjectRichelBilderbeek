//---------------------------------------------------------------------------

#ifndef UnitFormCdPlayerH
#define UnitFormCdPlayerH
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
#include "UnitTapButtonControl.h"
//Machine
struct CdPlayer;
//Control
//TapButton has already been #included
//Connect
struct CinchRedFemaleControl;
struct CinchWhiteFemaleControl;
struct ConnectorControl;
struct Plug220Control;
//Display
struct AudioSignalControl;
struct LcdSymbolPlayControl;
struct LcdSymbolRecControl;
struct LedControl;
//---------------------------------------------------------------------------
class TFormCdPlayer : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImagePlug220Power;
  TImage *ImageWatermark;
  TImage *ImageAudioSignalL;
  TImage *LabelConnectOut;
  TImage *ImageTapButtonPlay;
  TImage *ImageTapButtonStop;
  TImage *ImageAudioSignalR;
  TImage *ImageCinchFemaleOutL;
  TImage *ImageCinchFemaleOutR;
  TImage *ImageTapButtonPower;
  TImage *ImageLedPower;
  TImage *ImageLcdSymbolPlay;
  TTimer *TimerTick;
  void __fastcall TimerTickTimer(TObject *Sender);
private:	// User declarations
  //Machine
  boost::shared_ptr<CdPlayer> mCdPlayer;
  //Control
  boost::shared_ptr<TapButtonControl<CdPlayer> > mTapButtonPlay;
  boost::shared_ptr<TapButtonControl<CdPlayer> > mTapButtonStop;
  boost::shared_ptr<TapButtonControl<CdPlayer> > mTapButtonPower;
  //Connect
  boost::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleOutL;
  boost::shared_ptr<CinchRedFemaleControl> mCinchFemaleOutR;
  boost::shared_ptr<Plug220Control> mPlug220Power;
  //Display
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplayL;
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplayR;
  boost::shared_ptr<LcdSymbolPlayControl> mLcdSymbolPlay;
  boost::shared_ptr<LedControl> mLedPower;

public:		// User declarations
  __fastcall TFormCdPlayer(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCdPlayer *FormCdPlayer;
//---------------------------------------------------------------------------
#endif
