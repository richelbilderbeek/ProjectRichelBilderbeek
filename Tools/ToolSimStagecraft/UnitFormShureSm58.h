//---------------------------------------------------------------------------

#ifndef UnitFormShureSm58H
#define UnitFormShureSm58H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
struct ShureSm58;
struct XlrMaleControl;
//---------------------------------------------------------------------------
class TFormShureSm58 : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageXlrMale;
  TImage *ImageAudioSignal;
  TImage *ImageWatermark;
  TImage *ImageSing;
  TTimer *TimerSing;
  void __fastcall TimerSingTimer(TObject *Sender);
private:	// User declarations
  boost::shared_ptr<ShureSm58> mMicrophone;
  boost::shared_ptr<XlrMaleControl> mXlrMale;
  bool mSinging;
  const double mSingerAverage;
public:		// User declarations
  __fastcall TFormShureSm58(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormShureSm58 *FormShureSm58;
//---------------------------------------------------------------------------
#endif
