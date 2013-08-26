//---------------------------------------------------------------------------

#ifndef UnitFormSimStagecraftMainH
#define UnitFormSimStagecraftMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitEnumDisplayMode.h"
//#include "UnitConnectorState.h"
#include "UnitFormMachine.h"
//#include "UnitMachine.h"
//#include "UnitCable.h"
//struct TFormSoundTable;
//struct Connector;
struct ConnectorControl;
//---------------------------------------------------------------------------
class TFormSimStagecraftMain : public TForm
{
__published:	// IDE-managed Components
  TImage *ImageBuffer;
  TImage *ImageBackground;
  TTimer *TimerMain;
  TPanel *PanelBottom;
  TSpeedButton *ButtonView;
  TSpeedButton *ButtonUse;
  TSpeedButton *ButtonConnect;
  TImage *ImageQuit;
  TCheckBox *CheckBoxAutoMove;
  void __fastcall TimerMainTimer(TObject *Sender);
  void __fastcall OnButtonClick(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ImageQuitMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
  void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormResize(TObject *Sender);
private:	// User declarations
  //Variables
  std::vector<boost::shared_ptr<TFormMachine> > mMachines;
  ConnectorControl * mConnector1;
  ConnectorControl * mConnector2;
  EnumDisplayMode mDisplayMode;
  TFormMachine * mDragMachine;
  int mDragX;
  int mDragY;
  //Methods
  void PaintBackground();
  void TickBackground();
  void SetDisplayModes(const EnumDisplayMode mode);
  void UpdateBuffers();
  void AutoMove();
  void MoveAway(TRect& r1, TRect& r2);
  const int GetDrawingSurfaceHeight() const;
  const int GetDrawingSurfaceWidth() const;
  const bool OnFormMachine(const int x, const int y,
    const TFormMachine * const form) const;
  void TileMachines();

public:		// User declarations
  __fastcall TFormSimStagecraftMain(TComponent* Owner, const String selectedLevel);

  typedef std::vector<boost::shared_ptr<TFormMachine> >::iterator MachineIterator;
  typedef std::vector<boost::shared_ptr<TFormMachine> >::const_iterator ConstMachineIterator;

  void DrawScreen();
  void OnConnectorClick(ConnectorControl * const connector);
  void OnControllerClick();
};
//---------------------------------------------------------------------------
const bool InRect(const int x, const int y, const TRect& r);
//---------------------------------------------------------------------------
extern PACKAGE TFormSimStagecraftMain *FormSimStagecraftMain;
//---------------------------------------------------------------------------



#endif
