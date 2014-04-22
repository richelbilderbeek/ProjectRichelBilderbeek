//---------------------------------------------------------------------------
/*
    Met Z'n Drieën. A 3-player tic-tac-toe-like game.
    Copyright (C) 2010  Richel Bilderbeek

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

#include <boost/scoped_ptr.hpp>
#include "UnitFormOver.h"
#include "UnitFormAdditionalCopyright.h"
#include "UnitFormWhatsNew.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOver *FormOver;
//---------------------------------------------------------------------------
__fastcall TFormOver::TFormOver(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormOver::ButtonWhatsNewClick(TObject *Sender)
{
  boost::scoped_ptr<TFormWhatsNew> f(new TFormWhatsNew(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormOver::ButtonAdditionalCopyrightClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAdditionalCopyright> f(new TFormAdditionalCopyright(0));
  f->ShowModal();

}
//---------------------------------------------------------------------------

