//---------------------------------------------------------------------------

#ifndef UnitFormMdPlayerH
#define UnitFormMdPlayerH
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
struct MdPlayer;
//Control
//TapButton has already been #included
//Connect
struct CinchRedFemaleControl;
struct CinchWhiteFemaleControl;
struct Plug220Control;
//Display
struct AudioSignalControl;
struct LcdSymbolPlayControl;
struct LcdSymbolRecControl;
struct LedControl;
//---------------------------------------------------------------------------
class TFormMdPlayer : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageCinchFemaleInR;
  TImage *ImagePlug220Power;
  TImage *ImageWatermark;
  TImage *ImageAudioSignalL;
  TImage *LabelConnectIn;
  TImage *ImageCinchFemaleInL;
  TImage *LabelConnectOut;
  TImage *ImageTapButtonPlay;
  TImage *ImageTapButtonStop;
  TImage *ImageTapButtonRecord;
  TImage *ImageAudioSignalR;
  TImage *ImageCinchFemaleOutL;
  TImage *ImageCinchFemaleOutR;
  TImage *ImageTapButtonPower;
  TImage *ImageLedPower;
  TImage *ImageLcdSymbolPlay;
  TImage *ImageLcdSymbolRec;
private:	// User declarations
  //Machine
  boost::shared_ptr<MdPlayer> mMdPlayer;
  //Control
  boost::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonPlay;
  boost::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonRecord;
  boost::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonStop;
  boost::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonPower;
  //Connect
  boost::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleInL;
  boost::shared_ptr<CinchRedFemaleControl> mCinchFemaleInR;
  boost::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleOutL;
  boost::shared_ptr<CinchRedFemaleControl> mCinchFemaleOutR;
  boost::shared_ptr<Plug220Control> mPlug220Power;
  //Display
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplayL;
  boost::shared_ptr<AudioSignalControl> mAudioSignalDisplayR;
  boost::shared_ptr<LcdSymbolRecControl> mLcdSymbolRec;
  boost::shared_ptr<LcdSymbolPlayControl> mLcdSymbolPlay;
  boost::shared_ptr<LedControl> mLedPower;

public:		// User declarations
  __fastcall TFormMdPlayer(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMdPlayer *FormMdPlayer;
//---------------------------------------------------------------------------
#endif
