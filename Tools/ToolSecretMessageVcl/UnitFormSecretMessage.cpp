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
#include <vcl.h>
#pragma hdrstop

#include <boost/shared_ptr.hpp>

#include "UnitFormSecretMessage.h"
#include "UnitFormCreateSecret.h"
#include "UnitFormExtractSecret.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSecretMessage *FormSecretMessage;
//---------------------------------------------------------------------------
__fastcall TFormSecretMessage::TFormSecretMessage(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSecretMessage::PanelCreateMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  boost::shared_ptr<TFormCreateSecret> f(new TFormCreateSecret(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormSecretMessage::PanelExtractMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  boost::shared_ptr<TFormExtractSecret> f(new TFormExtractSecret(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormSecretMessage::PanelAboutMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  boost::shared_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

