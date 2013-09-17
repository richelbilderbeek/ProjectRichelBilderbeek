//---------------------------------------------------------------------------
/*
 *  Das Wahre Schlagerfest. A simple game.
 *  Copyright (C) 2003  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <AppEvnts.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
  TImage *ImageBratWurst;
  TImage *ImageBiertje;
  TApplicationEvents *ApplicationEvents1;
  TImage *ImageBackGround;
  TActionManager *ActionManager1;
  TAction *Find3Row;
  TAction *Initialize;
  TAction *DeletePlayer;
  TAction *DrawPlayer;
  TAction *DrawArea;
  TAction *ShowGameOver;
  TTimer *Timer1;
  TRichEdit *RichEdit1;
  TImage *ImageRichel;
        TImage *ImageAnimation;
        TImage *ImageMessage;
        TImage *ImagePressKeyDown;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall Find3RowExecute(TObject *Sender);
  void __fastcall InitializeExecute(TObject *Sender);
  void __fastcall DeletePlayerExecute(TObject *Sender);
  void __fastcall DrawPlayerExecute(TObject *Sender);
  void __fastcall DrawAreaExecute(TObject *Sender);
  void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
        void __fastcall FormClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
