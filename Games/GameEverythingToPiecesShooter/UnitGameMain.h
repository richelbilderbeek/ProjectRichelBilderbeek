//---------------------------------------------------------------------------

#ifndef UnitGameMainH
#define UnitGameMainH
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
#include "UnitSpriteIndexChanger.h"
#include "UnitKeyList.h"
//---------------------------------------------------------------------------
class TFormGameMain : public TForm
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
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  double mPlayerX;
  double mPlayerY;
  double mJumpY;
  int mSpriteX;
  int mSpriteY;
  const int mSpriteWidth;
  const int mSpriteHeight;
  //const double mPlayerAccel;
  const double mPlayerJumpAccel;
  const int mPlayerStep;
  double mSpeedX;
  double mSpeedY;
  int mSpriteIndex;
  //void getPlayerImage();
  SpriteIndexChanger mSpriteIndexChanger;
  KeyList mKeyList;
  void resizeImage(const TImage* image, const int& width,const int& height);
  void jump();
  void setSpriteIndex(const int& index);
public:		// User declarations
        __fastcall TFormGameMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGameMain *FormGameMain;
//---------------------------------------------------------------------------
#endif
