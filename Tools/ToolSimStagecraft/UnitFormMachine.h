//---------------------------------------------------------------------------

#ifndef UnitFormMachineH
#define UnitFormMachineH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitEnumDisplayMode.h"
struct Machine;
struct TFormSimStagecraftMain;
struct ConnectorControl;
//---------------------------------------------------------------------------
// Every FormMachine manages the GUI of one Machine
// A FormX manages a X
class TFormMachine : public TForm
{
__published:	// IDE-managed Components
  TImage *ImageBuffer;
  void __fastcall FormResize(TObject *Sender);
private:	// User declarations
protected:
  EnumDisplayMode mDisplayMode;
 
public:		// User declarations
  __fastcall TFormMachine(TComponent* Owner, TFormSimStagecraftMain * const formParent);
  //virtual const Machine * const GetMachine() const = 0; //Safe, because ~Machine is private
  void SetDisplayMode(const EnumDisplayMode mode) { mDisplayMode = mode; }
  virtual void UpdateBuffer() = 0;
  TFormSimStagecraftMain * const mFormParent; //const, so it be public
  virtual void OnMouseDown(const int x, const int y) {}
  virtual void OnMouseMove(const int x, const int y) {}
  virtual void OnMouseUp(const int x, const int y) {}
  virtual void OnAfterResize() {};  
  static const int mBorderSize = 8;
  void OnControllerClick();
  void OnConnectorClick(ConnectorControl * const connectorControl);
  void DrawOnBuffer(const TImage * const image);
  void DrawOnBuffer(const std::vector<TImage * const>& images);
  void DrawOnBuffer(const std::vector<TImage * >& images);
  void DrawBorderAroundBuffer();

};
//---------------------------------------------------------------------------
extern PACKAGE TFormMachine *FormMachine;
//---------------------------------------------------------------------------
#endif
