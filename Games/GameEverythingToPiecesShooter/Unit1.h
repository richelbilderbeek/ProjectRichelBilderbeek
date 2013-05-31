//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageSprites;
        TApplicationEvents *ApplicationEvents1;
        TImage *ImageBuffer;
        TImage *ImagePlayer;
        TImage *ImageBackground;
        TStatusBar *StatusBar1;
        TImageList *ImageList1;
        void __fastcall ApplicationEvents1Idle(TObject *Sender,
          bool &Done);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  double mPlayerX;
  double mPlayerY;
  double mJumpY;
  int mSpriteX;
  int mSpriteY;
  const int mSpriteWidth;
  const int mSpriteHeight;
  const double mPlayerAccel;
  const double mPlayerJumpAccel;
  double mSpeedX;
  double mSpeedY;
  int mSpriteIndex;
  //void getPlayerImage();
  void resizeImage(const TImage* image, const int& width,const int& height);
  void turnLeft();
  void turnRight();
  void pressUp();
  void pressDown();
  void jump();
  void setSpriteIndex(const int& index);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
