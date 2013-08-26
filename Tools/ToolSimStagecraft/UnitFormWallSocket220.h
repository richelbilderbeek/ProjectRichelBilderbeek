//---------------------------------------------------------------------------

#ifndef UnitFormWallSocket220H
#define UnitFormWallSocket220H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include <Buttons.hpp>
struct WallSocket220;
struct Socket220Control;
//---------------------------------------------------------------------------
class TFormWallSocket220 : public TFormMachine
{
__published:	// IDE-managed Components
  TImage *ImageView;
  TImage *ImageSocket220;
  TImage *ImageWatermark;
private:	// User declarations
  boost::shared_ptr<Socket220Control> mSocket220Control;
  boost::shared_ptr<WallSocket220> mSocket220;
public:		// User declarations
  __fastcall TFormWallSocket220(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWallSocket220 *FormWallSocket220;
//---------------------------------------------------------------------------
#endif
