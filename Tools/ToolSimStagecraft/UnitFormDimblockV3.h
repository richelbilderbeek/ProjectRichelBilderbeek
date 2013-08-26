//---------------------------------------------------------------------------

#ifndef UnitFormDimblockV3H
#define UnitFormDimblockV3H
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
struct DimblockV3;
struct SocketPowerMaleControl;
struct DmxMaleControl;
struct DmxFemaleControl;
struct Socket220Control;
struct LedControl;
//---------------------------------------------------------------------------
class TFormDimblockV3 : public TFormMachine
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageView;
  TImage *ImageDmxMaleInput;
  TImage *ImageDmxFemaleThrough;
  TImage *ImageSocketPowerMale;
  TImage *ImageSocket1;
  TImage *ImageSocket2;
  TImage *ImageSocket3;
  TImage *ImageSocket4;
  TImage *ImageSocket5;
  TImage *ImageSocket6;
  TImage *ImageSocket7;
  TImage *ImageSocket8;
  TImage *ImageSocket9;
  TImage *ImageSocket10;
  TImage *ImageSocket11;
  TImage *ImageSocket12;
  TImage *ImageLedMainsPower;
  TImage *ImageLedWarning;
  TImage *ImageLedNondimSet;
  TImage *ImageLedDmxPresent;
  TImage *ImageLedPresetSet;
  TImage *ImageWatermark;
  TImage *LabelConnectDmxIn;
  TImage *LabelConnectDmxThrough;
  TImage *LabelConnectMains;
  TImage *LabelConnect1;
  TImage *LabelConnect2;
  TImage *LabelConnect3;
  TImage *LabelConnect4;
  TImage *LabelConnect5;
  TImage *LabelConnect6;
  TImage *Image10;
  TImage *Image11;
  TImage *Image12;
  TImage *Image13;
  TImage *Image14;
  TImage *Image15;
  TImage *LabelConnect7;
  TImage *LabelConnect8;
  TImage *LabelConnect9;
  TImage *LabelConnect10;
  TImage *LabelConnect11;
  TImage *LabelConnect12;
  TImage *LabelUseMainsPower;
  TImage *LabelUseNondimSet;
  TImage *LabelUsePresetSet;
  TImage *LabelUseDmxPresent;
  TImage *LabelUseWarning;
private:	// User declarations
  //Machine
  boost::shared_ptr<DimblockV3> mDimblockV3;
  //Control
  //Connect
  boost::shared_ptr<DmxMaleControl> mDmxMaleInput;
  boost::shared_ptr<DmxFemaleControl> mDmxFemaleThrough;
  boost::shared_ptr<SocketPowerMaleControl> mSocketPowerMale;
  //Display
  boost::shared_ptr<LedControl> mLedMainsPower;
  boost::shared_ptr<LedControl> mLedNondimSet;
  boost::shared_ptr<LedControl> mLedPresetSet;
  boost::shared_ptr<LedControl> mLedDmxPresent;
  boost::shared_ptr<LedControl> mLedWarning;
  //Other
  std::vector<boost::shared_ptr<Socket220Control> > mSockets;
  std::vector<TImage*> mImageSockets;
  const std::vector<boost::shared_ptr<Socket220Control> >
    CreateSocket220Controls();
public:		// User declarations
  __fastcall TFormDimblockV3(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();
  const TImage * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDimblockV3 *FormDimblockV3;
//---------------------------------------------------------------------------
#endif
