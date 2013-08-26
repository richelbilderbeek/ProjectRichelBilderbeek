//---------------------------------------------------------------------------

#ifndef UnitFormSimStagecraftAboutH
#define UnitFormSimStagecraftAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSimStagecraftAbout : public TForm
{
__published:	// IDE-managed Components
  TImage *ImageBackground;
  TPanel *Panel1;
  TRichEdit *RichEditLicence;
  TPanel *Panel2;
  TPanel *Panel3;
  TPanel *Panel4;
  TPanel *Panel5;
  TPanel *Panel6;
  TPanel *Panel7;
  TTimer *TimerMain;
  TTimer *TimerColor;
        TButton *ButtonWhatsNew;
        TButton *ButtonOtherLicences;
        TPanel *Panel8;
  void __fastcall TimerMainTimer(TObject *Sender);
  void __fastcall TimerColorTimer(TObject *Sender);
        void __fastcall ButtonWhatsNewClick(TObject *Sender);
        void __fastcall ButtonOtherLicencesClick(TObject *Sender);
private:	// User declarations
  int mDr;
  int mDg;
  int mDb;
  void DrawBackground();
public:		// User declarations
  __fastcall TFormSimStagecraftAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimStagecraftAbout *FormSimStagecraftAbout;
//---------------------------------------------------------------------------
#endif
