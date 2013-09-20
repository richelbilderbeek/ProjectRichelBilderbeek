//---------------------------------------------------------------------------

#ifndef StringmatcherH
#define StringmatcherH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TOpenDialog *OpenDialog2;
        TSaveDialog *SaveDialog1;
        TMemo *OpenMemo1;
        TMemo *OpenMemo2;
        TPanel *OpenPanel1;
        TPanel *OpenPanel2;
        TButton *OpenButton1;
        TButton *OpenButton2;
        TPanel *MatchPanel;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TButton *MatchButton;
        TPanel *SavePanel;
        TMemo *SaveMemo;
        TButton *SaveButton;
        TImage *Image1;
        TButton *ToSaveButton1;
        TButton *ToSaveButton2;
        TButton *CombineButton1;
        TButton *CombineButton2;
        TButton *DubbelButton1;
        TButton *DubbelButton2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TPanel *AdvancedPanel;
        TButton *HideButton;
        TLabel *Label4;
        TLabel *Label5;
        TButton *DetermineButton;
        TCheckBox *DifferentBox;
        TEdit *ValueField;
        TLabel *AnsiPosLabel;
        TLabel *Label6;
        void __fastcall OpenButton1Click(TObject *Sender);
        void __fastcall OpenButton2Click(TObject *Sender);
        void __fastcall OpenDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall OpenDialog2CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall SaveDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall MatchButtonClick(TObject *Sender);
        void __fastcall ToSaveButton1Click(TObject *Sender);
        void __fastcall ToSaveButton2Click(TObject *Sender);
        void __fastcall CombineButton1Click(TObject *Sender);
        void __fastcall CombineButton2Click(TObject *Sender);
        void __fastcall DubbelButton1Click(TObject *Sender);
        void __fastcall DubbelButton2Click(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall HideButtonClick(TObject *Sender);
        void __fastcall DetermineButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
