//---------------------------------------------------------------------------

#ifndef UnitFormPrsH
#define UnitFormPrsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
enum EnumPrs { paper, rock, scissors };
class TFormChart;
//---------------------------------------------------------------------------
class TFormPrs : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelMenu;
        TButton *ButtonPlayPause;
        TButton *ButtonReset;
        TEdit *EditWidth;
        TEdit *EditHeight;
        TLabel *LabelWidth;
        TLabel *LabelHeight;
        TButton *ButtonAbout;
        TImage *ImageArea;
        TTimer *Timer1;
        TCheckBox *CheckBoxShow;
        void __fastcall EditChange(TObject *Sender);
        void __fastcall ButtonResetClick(TObject *Sender);
        void __fastcall ButtonPlayPauseClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall CheckBoxShowClick(TObject *Sender);
private:	// User declarations
  std::vector<std::vector<EnumPrs> > mV;
  void DrawInitialArea();
  void DrawArea();
  void CountPopulation() const;
  std::auto_ptr<TFormChart> mFormChart;
public:		// User declarations
        __fastcall TFormPrs(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPrs *FormPrs;
//---------------------------------------------------------------------------
#endif
