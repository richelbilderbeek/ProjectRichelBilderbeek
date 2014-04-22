//---------------------------------------------------------------------------

#ifndef UnitFormGameH
#define UnitFormGameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <set>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "UnitArea.h"
//#include "UnitFormArea.h"
struct TFormArea;
//---------------------------------------------------------------------------
class TFormGame : public TForm
{
__published:	// IDE-managed Components
        TTimer *TimerMain;
        TImage *ImageBuffer;
        void __fastcall TimerMainTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations

  typedef std::vector<Area>::iterator AreaIterator;
  std::vector<Area> m_areas;
  AreaIterator m_cur_area;
  int m_n_lives;
  std::set<WORD> m_keys;
  void NewArea();

public:		// User declarations
  __fastcall TFormGame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGame *FormGame;
//---------------------------------------------------------------------------
#endif
