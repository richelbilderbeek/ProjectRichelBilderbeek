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
#ifndef UnitFormCreateSecretH
#define UnitFormCreateSecretH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormCreateSecret : public TForm
{
__published:	// IDE-managed Components
  TPanel *PanelCreateSecret;
  TImage *ImageResult;
  TImage *ImageMessage;
  TImage *ImageOriginal;
  TOpenPictureDialog *OpenDialog;
  TSavePictureDialog *SaveDialog;
  TPanel *PanelLoadOriginal;
  TPanel *PanelLoadMessage;
  TPanel *PanelSave;
  void __fastcall PanelLoadOriginalMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall PanelLoadMessageMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall PanelSaveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormCreateSecret(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCreateSecret *FormCreateSecret;
//---------------------------------------------------------------------------
#endif
