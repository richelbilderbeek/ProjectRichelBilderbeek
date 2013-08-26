//---------------------------------------------------------------------------

#ifndef UnitFormSpritesH
#define UnitFormSpritesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
//TFormSprites is a global TForm
//TFormSprites MUST be created before a TFormSimStagecraft is created
class TFormSprites : public TForm
{
__published:	// IDE-managed Components
  TPageControl *PageControl;
  TTabSheet *TabSheetView;
  TTabSheet *TabSheetUse;
  TTabSheet *TabSheetConnect;
  TImage *ImageSocket220;
  TImage *ImageSocket220Selected;
  TImage *ImageSocket220Connected;
  TImage *ImageSocket220ConnectedSelected;
  TImage *ImagePlug220;
  TImage *ImagePlug220Selected;
  TImage *ImagePlug220Connected;
  TImage *ImagePlug220ConnectedSelected;
  TImage *ImageXlrFemale;
  TImage *ImageXlrFemaleSelected;
  TImage *ImageXlrFemaleConnected;
  TImage *ImageXlrFemaleConnectedSelected;
  TImage *ImageXlrMaleConnected;
  TImage *ImageXlrMaleConnectedSelected;
  TImage *ImageXlrMaleSelected;
  TImage *ImageXlrMale;
  TImage *ImageEuroMale;
  TImage *ImageEuroMaleSelected;
  TImage *ImageEuroMaleConnected;
  TImage *ImageEuroMaleConnectedSelected;
  TImage *ImageRedLedOff;
  TImage *ImageRedLedOn;
  TImage *ImageTwoSwitchOff;
  TImage *ImageTwoSwitchOn;
  TImage *ImageGreenLedOff;
  TImage *ImageGreenLedOn;
  TImage *ImageDmxFemale;
  TImage *ImageDmxFemaleSelected;
  TImage *ImageDmxFemaleConnected;
  TImage *ImageDmxFemaleConnectedSelected;
  TImage *ImageSocketPowerFemale;
  TImage *ImageSocketPowerMale;
  TImage *ImageDmxMale;
  TImage *ImageDmxMaleSelected;
  TImage *ImageDmxMaleConnected;
  TImage *ImageDmxMaleConnectedSelected;
  TImage *ImageSocketPowerFemaleSelected;
  TImage *ImageSocketPowerMaleSelected;
  TImage *ImageSocketPowerFemaleConnected;
  TImage *ImageSocketPowerFemaleConnectedSelected;
  TImage *ImageSocketPowerMaleConnected;
  TImage *ImageSocketPowerMaleConnectedSelected;
  TImage *ImageYellowLedOff;
  TImage *ImageYellowLedOn;
  TImage *ImageSingYes;
  TImage *ImageSingNo;
  TImage *ImagePressButtonOut;
  TImage *ImagePressButtonIn;
  TImage *ImageJackFemale;
  TImage *ImageJackFemaleSelected;
  TImage *ImageJackFemaleConnectedSelected;
  TImage *ImageJackFemaleConnected;
  TImage *ImageCinchFemaleWhite;
  TImage *ImageCinchFemaleWhiteSelected;
  TImage *ImageCinchFemaleWhiteConnected;
  TImage *ImageCinchFemaleWhiteConnectedSelected;
  TImage *ImageCinchFemaleRed;
  TImage *ImageCinchFemaleRedSelected;
  TImage *ImageCinchFemaleRedConnected;
  TImage *ImageCinchFemaleRedConnectedSelected;
  TImage *ImageLcdSymbolPlay;
  TImage *ImageLcdSymbolRec;
  TImage *ImageJackMale;
  TImage *ImageJackMaleSelected;
  TImage *ImageJackMaleConnected;
  TImage *ImageJackMaleConnectedSelected;
        TImage *ImageSpeakonFemale;
        TImage *ImageSpeakonFemaleSelected;
        TImage *ImageSpeakonFemaleConnected;
        TImage *ImageSpeakonFemaleConnectedSelected;
        TImage *ImageEuroFemale;
        TImage *ImageEuroFemaleSelected;
        TImage *ImageEuroFemaleConnected;
        TImage *ImageEuroFemaleConnectedSelected;
        TImage *ImageSpeakonMale;
        TImage *ImageSpeakonMaleSelected;
        TImage *ImageSpeakonMaleConnected;
        TImage *ImageSpeakonMaleConnectedSelected;
        TImage *ImageCinchMaleWhite;
        TImage *ImageCinchMaleWhiteSelected;
        TImage *ImageCinchMaleWhiteConnected;
        TImage *ImageCinchMaleWhiteConnectedSelected;
        TImage *ImageCinchMaleRed;
        TImage *ImageCinchMaleRedSelected;
        TImage *ImageCinchMaleRedConnected;
        TImage *ImageCinchMaleRedConnectedSelected;
        TImage *ImageJackXlrFemale;
        TImage *ImageJackXlrFemaleSelected;
        TImage *ImageJackXlrFemaleConnected;
        TImage *ImageJackXlrFemaleConnectedSelected;
private:	// User declarations
public:		// User declarations
  __fastcall TFormSprites(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSprites *FormSprites;
//---------------------------------------------------------------------------
#endif
