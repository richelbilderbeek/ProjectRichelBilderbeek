//---------------------------------------------------------------------------

#ifndef UnitFormSimStagecraftSelectH
#define UnitFormSimStagecraftSelectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSimStagecraftSelect : public TForm
{
__published:	// IDE-managed Components
  TImage *ImageSelectLevel;
  TRichEdit *RichEdit;
  TImage *Image2;
  TImage *Image1;
  TImage *Image3;
  TImage *Image4;
  TImage *Image5;
  TImage *Image6;
  TImage *Image7;
  TImage *Image8;
  TImage *Image9;
  TImage *Image0;
  TImage *ImageArrowLeft;
  TImage *ImageArrowRight;
  TImage *ImageSelectRight;
  TImage *ImageSelectLeft;
  TImage *ImageStart;
  TImage *ImageBuffer;
  TImage *ImageBackground;
  TTimer *TimerMain;
  TImage *ImageQuit;
  TImage *ImageLed4;
  TImage *ImageLed2;
  TImage *ImageLed1;
  TImage *ImageLed3;
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall TimerMainTimer(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  int mLevel;
  const int mBorderSize;
  std::vector<TImage *> mImages;
  const bool OnImage(const int x, const int y,
    const TImage * const image) const;
  TImage * const GetImage(const int value) const;
  void DrawScreen();
  void PaintBackground();
  void TickBackground();
  void UpdateText();
public:		// User declarations
  __fastcall TFormSimStagecraftSelect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimStagecraftSelect *FormSimStagecraftSelect;
//---------------------------------------------------------------------------
#endif
