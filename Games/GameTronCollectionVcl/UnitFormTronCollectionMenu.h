//---------------------------------------------------------------------------

#ifndef UnitFormTronCollectionMenuH
#define UnitFormTronCollectionMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormTronCollectionMenu : public TForm
{
__published:	// IDE-managed Components
  TPanel *PanelTitle;
  TImage *ImageClassicTron;
  TImage *ImageSuperTron;
  TImage *ImageUltimateTron;
  void __fastcall ImageClassicTronMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall ImageSuperTronMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall ImageUltimateTronMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TFormTronCollectionMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTronCollectionMenu *FormTronCollectionMenu;
//---------------------------------------------------------------------------
#endif
