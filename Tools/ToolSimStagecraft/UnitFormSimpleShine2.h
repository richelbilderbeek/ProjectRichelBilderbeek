//---------------------------------------------------------------------------

#ifndef UnitFormSimpleShine2H
#define UnitFormSimpleShine2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include "UnitFormMachine.h"
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitFormMachine.h"
struct SimpleShine2;
struct FaderControl;
struct SimpleShine1;
struct DmxFemaleControl;
struct EuroMaleControl;
//---------------------------------------------------------------------------
class TFormSimpleShine2 : public TFormMachine
{
__published:	// IDE-managed Components
  TImage *ImageView;
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageFaderMaster;
  TImage *ImageFader1;
  TImage *ImageEuroMalePower;
  TImage *ImageDmxFemaleOut;
  TImage *ImageWatermark;
  TImage *LabelUseMaster;
  TImage *ImageFader2;
  TImage *ImageFader3;
  TImage *ImageFader4;
  TImage *ImageFader5;
  TImage *ImageFader6;
  TImage *ImageFader7;
  TImage *ImageFader8;
  TImage *ImageFader9;
  TImage *ImageFader10;
  TImage *ImageFader11;
  TImage *ImageFader12;
  TImage *LabelConnectPower;
  TImage *LabelConnectDmxOut;
        TImage *LabelUseSimpleShine2;
  TImage *ImageLedPower;
        TImage *ImageFader13;
        TImage *ImageFader14;
        TImage *ImageFader15;
        TImage *ImageFader16;
        TImage *ImageFader17;
        TImage *ImageFader18;
        TImage *ImageFader19;
        TImage *ImageFader20;
        TImage *ImageFader21;
        TImage *ImageFader22;
        TImage *ImageFader23;
        TImage *ImageFader24;
        TImage *LabelUse2_2;
        TImage *LabelUse1_2;
        TImage *LabelUse3_2;
        TImage *LabelUse4_2;
        TImage *LabelUse5_2;
        TImage *LabelUse6_2;
        TImage *LabelUse7_2;
        TImage *LabelUse8_2;
        TImage *LabelUse9_2;
        TImage *LabelUse10_2;
        TImage *LabelUse11_2;
        TImage *LabelUse12_2;
        TImage *LabelUse1_3;
        TImage *LabelUse2_3;
        TImage *LabelUse3_3;
        TImage *LabelUse4_3;
        TImage *LabelUse5_3;
        TImage *LabelUse6_3;
        TImage *LabelUse7_3;
        TImage *LabelUse8_3;
        TImage *LabelUse9_3;
        TImage *LabelUse10_3;
        TImage *LabelUse11_3;
        TImage *LabelUse12_3;
        TImage *LabelUse3_1;
        TImage *LabelUse1_1;
        TImage *LabelUse2_1;
        TImage *LabelUse4_1;
        TImage *LabelUse5_1;
        TImage *LabelUse6_1;
        TImage *LabelUse7_1;
        TImage *LabelUse8_1;
        TImage *LabelUse9_1;
        TImage *LabelUse10_1;
        TImage *LabelUse11_1;
        TImage *LabelUse12_1;
        TImage *ImageCrossfaderB;
        TImage *ImageCrossfaderA;
        TImage *LabelUseCrossfader;
        TImage *ImageLedA;
        TImage *ImageLedB;
private:	// User declarations
  //Machine
  boost::shared_ptr<SimpleShine2> mSimpleShine2;
  //Control
  const std::vector<TImage*> mImageFaders;
  const std::vector<TImage*> mLabels;
  const std::vector<TImage*> GetImageFaders() const;
  const std::vector<TImage*> GetLabels() const;
  std::vector<boost::shared_ptr<FaderControl> > mChannelFaders;
  boost::shared_ptr<FaderControl> mCrossfaderA;
  boost::shared_ptr<FaderControl> mCrossfaderB;
  boost::shared_ptr<FaderControl> mMasterFader;
  //Connect
  boost::shared_ptr<DmxFemaleControl> mDmxFemaleOut;
  boost::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  boost::shared_ptr<LedControl> mLedPower;
  boost::shared_ptr<LedControl> mLedA;
  boost::shared_ptr<LedControl> mLedB;
public:		// User declarations
  __fastcall TFormSimpleShine2(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  const TImage * const GetImageBuffer() const;
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();

};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimpleShine2 *FormSimpleShine2;
//---------------------------------------------------------------------------
#endif
