//---------------------------------------------------------------------------

#ifndef UnitFormMenuH
#define UnitFormMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormMenu : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelStart;
        TImage *ImageBillyLogo;
        TTimer *TimerAutoStart;
        TPanel *PanelAbout;
        TPanel *PanelQuit;
        void __fastcall PanelStartClick(TObject *Sender);
        void __fastcall TimerAutoStartTimer(TObject *Sender);
        void __fastcall PanelQuitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMenu *FormMenu;
//---------------------------------------------------------------------------
#endif
