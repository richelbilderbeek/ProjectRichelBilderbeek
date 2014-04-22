#ifndef UnitFormWhatsNewH
#define UnitFormWhatsNewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormWhatsNew : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit;
private:	// User declarations
public:		// User declarations
        __fastcall TFormWhatsNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWhatsNew *FormWhatsNew;
//---------------------------------------------------------------------------
#endif
