//---------------------------------------------------------------------------

#ifndef UnitFormWallSocketPowerH
#define UnitFormWallSocketPowerH
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
struct WallSocketPower;
struct SocketPowerFemaleControl;
//---------------------------------------------------------------------------
class TFormWallSocketPower : public TFormMachine
{
__published:	// IDE-managed Components
  TImage *ImageView;
  TImage *ImageSocketPower;
  TImage *ImageWatermark;
private:	// User declarations
  boost::shared_ptr<SocketPowerFemaleControl> mSocketPowerControl;
  boost::shared_ptr<WallSocketPower> mSocketPower;
public:		// User declarations
  __fastcall TFormWallSocketPower(TComponent* Owner,
    TFormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();

  const TImage * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWallSocketPower *FormWallSocketPower;
//---------------------------------------------------------------------------
#endif
