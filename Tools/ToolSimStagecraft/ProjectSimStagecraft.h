//---------------------------------------------------------------------------

#ifndef ProjectSimStagecraftH
#define ProjectSimStagecraftH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class TFormSimStagecraftMenu : public TForm
{
__published:	// IDE-managed Components
  TImage *ImageTitle;
  TImage *ImageAbout;
  TImage *ImageQuit;
  TImage *ImageStart;
  TImage *Image1;
  TImage *Image4;
  TImage *Image5;
  TImage *Image2;
  TImage *Image3;
  TImage *Image6;
  TImage *ImageBackground;
  TTimer *TimerBackground;
  TImage *ImageBuffer;
  void __fastcall FormResize(TObject *Sender);
  void __fastcall TimerBackgroundTimer(TObject *Sender);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  void PaintBackground();
  void TickBackground();
  void DrawScreen();
  const std::vector<TImage*> mImages;
  const std::vector<TImage*> GetImages() const;
  const int mBorderSize;
public:		// User declarations
  __fastcall TFormSimStagecraftMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimStagecraftMenu *FormSimStagecraftMenu;
//---------------------------------------------------------------------------
#endif
