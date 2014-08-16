//---------------------------------------------------------------------------
/*
 *  The Image Rotater (CLX edition). Rotates 24-bit bitmaps
 *  Copyright (C) 2007  Richel Bilderbeek
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
#ifndef UnitFormAboutClxH
#define UnitFormAboutClxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QExtCtrls.hpp>
#include <QGraphics.hpp>
//---------------------------------------------------------------------------
class TFormAbout : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TMemo *Memo1;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel4;
        TPanel *Panel7;
        TPanel *Panel9;
private:	// User declarations
public:		// User declarations
        __fastcall TFormAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAbout *FormAbout;
//---------------------------------------------------------------------------
#endif
