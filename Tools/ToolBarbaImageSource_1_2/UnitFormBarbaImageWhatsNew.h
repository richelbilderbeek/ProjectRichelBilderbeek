//---------------------------------------------------------------------------

#ifndef UnitFormBarbaImageWhatsNewH
#define UnitFormBarbaImageWhatsNewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormBarbaImageWhatsNew : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit;
private:	// User declarations
public:		// User declarations
        __fastcall TFormBarbaImageWhatsNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBarbaImageWhatsNew *FormBarbaImageWhatsNew;
//---------------------------------------------------------------------------
#endif
