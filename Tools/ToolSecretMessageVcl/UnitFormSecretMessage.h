//---------------------------------------------------------------------------
/*
  Secret Message, tool to add secret messages to images
  Copyright (C) 2009  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitFormSecretMessageH
#define UnitFormSecretMessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSecretMessage : public TForm
{
__published:	// IDE-managed Components
  TPanel *PanelCreate;
  TPanel *PanelExtract;
  TPanel *PanelAbout;
  void __fastcall PanelCreateMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall PanelExtractMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall PanelAboutMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
  __fastcall TFormSecretMessage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSecretMessage *FormSecretMessage;
//---------------------------------------------------------------------------
#endif
