//---------------------------------------------------------------------------

#ifndef UnitFormRcfEvent3000H
#define UnitFormRcfEvent3000H
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
struct RcfEvent3000;
//Control
//Connect
struct SpeakonFemaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class TFormRcfEvent3000 : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageWatermark;
  TImage *ImageSound;
        TImage *ImageInput;
        TImage *ImageLink;
private:	// User declarations
  //Machine
  boost::shared_ptr<RcfEvent3000> mSpeaker;
  //Control
  //Connect
  boost::shared_ptr<SpeakonFemaleControl> mInput;
  boost::shared_ptr<SpeakonFemaleControl> mLink;
  //Display
  //RCF Event 3000 does not use the DisplayControl
  //because it is not an actual physical electrical display 
  //boost::shared_ptr<AudioSignalControl> mDisplay;
public:		// User declarations
  __fastcall TFormRcfEvent3000(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRcfEvent3000 *FormRcfEvent3000;
//---------------------------------------------------------------------------
#endif
