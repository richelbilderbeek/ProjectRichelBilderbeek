//---------------------------------------------------------------------------

#ifndef UnitFormSpritesH
#define UnitFormSpritesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSprites : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageMainCharStandRight;
        TImage *ImageMainCharWalkRight1;
        TImage *ImageMainCharWalkRight2;
        TImage *ImageMainCharJumpRight;
        TImage *ImageMainCharHangRight;
        TImage *ImageAlForest;
        TImage *ImagePuddle;
        TImage *ImageApple;
        TImage *ImageRock;
        TImage *Image1;
        TImage *ImageBall;
        TImage *ImageMainCharStandLeft;
        TImage *ImageMainCharWalkLeft1;
        TImage *ImageMainCharWalkLeft2;
        TImage *ImageMainCharJumpLeft;
        TImage *ImageMainCharHangLeft;
private:	// User declarations
public:		// User declarations
        __fastcall TFormSprites(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSprites *FormSprites;
//---------------------------------------------------------------------------
#endif
